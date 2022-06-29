/*
 * Copyright (c) 2020, HiHope Community.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "aht2x.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "hi_i2c.h"
#include "hi_errno.h"
#include "polygon_sys_cfg.h"
#include "hal_pz_i2c.h"

#if HARDWARE_TYPE == HW_TYPE_TIANQI
#define AHT20_I2C_IDX HI_I2C_IDX_1

#define AHT20_STARTUP_TIME     20*1000 // 上电启动时间
#define AHT20_CALIBRATION_TIME 40*1000 // 初始化（校准）时间
#define AHT20_MEASURE_TIME     75*1000 // 测量时间

#define AHT20_DEVICE_ADDR   0x38
#define AHT20_READ_ADDR     ((0x38<<1)|0x1)
#define AHT20_WRITE_ADDR    ((0x38<<1)|0x0)

#define AHT20_CMD_CALIBRATION       0xBE // 初始化（校准）命令
#define AHT20_CMD_CALIBRATION_ARG0  0x08
#define AHT20_CMD_CALIBRATION_ARG1  0x00

/**
 * 传感器在采集时需要时间,主机发出测量指令（0xAC）后，延时75毫秒以上再读取转换后的数据并判断返回的状态位是否正常。
 * 若状态比特位[Bit7]为0代表数据可正常读取，为1时传感器为忙状态，主机需要等待数据处理完成。
 **/
#define AHT20_CMD_TRIGGER       0xAC // 触发测量命令
#define AHT20_CMD_TRIGGER_ARG0  0x33
#define AHT20_CMD_TRIGGER_ARG1  0x00

// 用于在无需关闭和再次打开电源的情况下，重新启动传感器系统，软复位所需时间不超过20 毫秒
#define AHT20_CMD_RESET      0xBA // 软复位命令

#define AHT20_CMD_STATUS     0x71 // 获取状态命令

/**
 * STATUS 命令回复：
 * 1. 初始化后触发测量之前，STATUS 只回复 1B 状态值；
 * 2. 触发测量之后，STATUS 回复6B： 1B 状态值 + 2B 湿度 + 4b湿度 + 4b温度 + 2B 温度
 *      RH = Srh / 2^20 * 100%
 *      T  = St  / 2^20 * 200 - 50
 **/
#define AHT20_STATUS_BUSY_SHIFT 7       // bit[7] Busy indication
#define AHT20_STATUS_BUSY_MASK  (0x1<<AHT20_STATUS_BUSY_SHIFT)
#define AHT20_STATUS_BUSY(status) ((status & AHT20_STATUS_BUSY_MASK) >> AHT20_STATUS_BUSY_SHIFT)

#define AHT20_STATUS_MODE_SHIFT 5       // bit[6:5] Mode Status
#define AHT20_STATUS_MODE_MASK  (0x3<<AHT20_STATUS_MODE_SHIFT)
#define AHT20_STATUS_MODE(status) ((status & AHT20_STATUS_MODE_MASK) >> AHT20_STATUS_MODE_SHIFT)

                                        // bit[4] Reserved
#define AHT20_STATUS_CALI_SHIFT 3       // bit[3] CAL Enable
#define AHT20_STATUS_CALI_MASK  (0x1<<AHT20_STATUS_CALI_SHIFT)
#define AHT20_STATUS_CALI(status) ((status & AHT20_STATUS_CALI_MASK) >> AHT20_STATUS_CALI_SHIFT)
                                        // bit[2:0] Reserved

#define AHT20_STATUS_RESPONSE_MAX 6

#define AHT20_RESLUTION            (1<<20)  // 2^20

#define AHT20_MAX_RETRY 10

static hi_u32 AHT20_Read(hi_u8* buffer, hi_u32 buffLen)
{
	/*
    hi_i2c_data data = { 0 };
    data.receive_buf = buffer;
    data.receive_len = buffLen;
    hi_u32 retval = hi_i2c_read(AHT20_I2C_IDX, AHT20_READ_ADDR, &data);
    if (retval != HI_ERR_SUCCESS) {
        printf("hi_i2c_read() failed, %0X!\n", retval);
        return retval;
    }
    return HI_ERR_SUCCESS;
    */
    return hal_pz_i2c_read(AHT20_I2C_IDX,AHT20_DEVICE_ADDR,buffer,buffLen);
}

static hi_u32 AHT20_Write(hi_u8* buffer, hi_u32 buffLen)
{
	/*
    hi_i2c_data data = { 0 };
    data.send_buf = buffer;
    data.send_len = buffLen;
    hi_u32 retval = hi_i2c_write(AHT20_I2C_IDX, AHT20_WRITE_ADDR, &data);
    if (retval != HI_ERR_SUCCESS) {
        printf("hi_i2c_write(%02X) failed, %0X!\n", buffer[0], retval);
        return retval;
    }
    return HI_ERR_SUCCESS;
    */
    return hal_pz_i2c_write(AHT20_I2C_IDX,AHT20_DEVICE_ADDR,buffer,buffLen);
}

// 发送获取状态命令
static hi_u32 AHT20_StatusCommand(void)
{
    hi_u8 statusCmd[] = { AHT20_CMD_STATUS };
    return AHT20_Write(statusCmd, sizeof(statusCmd));
}

// 发送软复位命令
static hi_u32 AHT20_ResetCommand(void)
{
    hi_u8 resetCmd[] = {AHT20_CMD_RESET};
    return AHT20_Write(resetCmd, sizeof(resetCmd));
}

// 发送初始化校准命令
static hi_u32 AHT20_CalibrateCommand(void)
{
    hi_u8 clibrateCmd[] = {AHT20_CMD_CALIBRATION, AHT20_CMD_CALIBRATION_ARG0, AHT20_CMD_CALIBRATION_ARG1};
    return AHT20_Write(clibrateCmd, sizeof(clibrateCmd));
}

// 读取温湿度值之前， 首先要看状态字的校准使能位Bit[3]是否为 1(通过发送0x71可以获取一个字节的状态字)，
// 如果不为1，要发送0xBE命令(初始化)，此命令参数有两个字节， 第一个字节为0x08，第二个字节为0x00。
hi_u32 AHT20_Calibrate(void)
{
    hi_u32 retval = 0;
    hi_u8 buffer[AHT20_STATUS_RESPONSE_MAX] = { AHT20_CMD_STATUS };
    memset(&buffer, 0x0, sizeof(buffer));

    retval = AHT20_StatusCommand();
    if (retval != HI_ERR_SUCCESS) {
        return retval;
    }

    retval = AHT20_Read(buffer, sizeof(buffer));
    if (retval != HI_ERR_SUCCESS) {
        return retval;
    }

    if (AHT20_STATUS_BUSY(buffer[0]) || !AHT20_STATUS_CALI(buffer[0])) {
        retval = AHT20_ResetCommand();
        if (retval != HI_ERR_SUCCESS) {
            return retval;
        }
        usleep(AHT20_STARTUP_TIME);
        retval = AHT20_CalibrateCommand();
        usleep(AHT20_CALIBRATION_TIME);
        return retval;
    }
    return HI_ERR_SUCCESS;
}

// 发送 触发测量 命令，开始测量
hi_u32 AHT20_StartMeasure(void)
{
    hi_u8 triggerCmd[] = {AHT20_CMD_TRIGGER, AHT20_CMD_TRIGGER_ARG0, AHT20_CMD_TRIGGER_ARG1};
    return AHT20_Write(triggerCmd, sizeof(triggerCmd));
}

// 接收测量结果，拼接转换为标准值
int AHT20_GetMeasureResult(float* temp, float* humi)
{
    hi_u32 retval = 0, i = 0;
    if (temp == NULL || humi == NULL) {
        //printf("input para is null\r\n");
        return -1;
    }
    // start measure
    retval = AHT20_StartMeasure();
    if (retval != HI_ERR_SUCCESS) {
        //printf("trigger measure failed!\r\n");
        return -1;
    }
    // get result
    hi_u8 buffer[AHT20_STATUS_RESPONSE_MAX] = { 0 };
    memset(&buffer, 0x0, sizeof(buffer));
    retval = AHT20_Read(buffer, sizeof(buffer));  // recv status command result
    if (retval != HI_ERR_SUCCESS) {
        //printf("aht2x read failed!\r\n");
        return -1;
    }
    for (i = 0; AHT20_STATUS_BUSY(buffer[0]) && i < AHT20_MAX_RETRY; i++) {
        // printf("AHT20 device busy, retry %d/%d!\r\n", i, AHT20_MAX_RETRY);
        usleep(AHT20_MEASURE_TIME);
        retval = AHT20_Read(buffer, sizeof(buffer));  // recv status command result
        if (retval != HI_ERR_SUCCESS) {
            //printf("aht2x read failed!\r\n");
            return -1;
        }
    }
    if (i >= AHT20_MAX_RETRY) {
        //printf("AHT20 device always busy!\r\n");
        return -1;
    }

    hi_u32 humiRaw = buffer[1];
    humiRaw = (humiRaw << 8) | buffer[2];
    humiRaw = (humiRaw << 4) | ((buffer[3] & 0xF0) >> 4);
    *humi = humiRaw / (float)AHT20_RESLUTION * 100;

    hi_u32 tempRaw = buffer[3] & 0x0F;
    tempRaw = (tempRaw << 8) | buffer[4];
    tempRaw = (tempRaw << 8) | buffer[5];
    *temp = tempRaw / (float)AHT20_RESLUTION * 200 - 50;
    // printf("humi = %05X, %f, temp= %05X, %f\r\n", humiRaw, *humi, tempRaw, *temp);
    return 0;
}

hi_void aht2x_prepare()
{
    hi_u8 try_cnt = 0;
    while (HI_ERR_SUCCESS != AHT20_Calibrate()) {
        printf("AHT20 sensor init failed, retry...\r\n");
        hi_udelay(1000);
        if(try_cnt++ > 5){
            printf("AHT20 sensor init failed!\r\n");
            break;
        }
    }
}

int tqs1_aht2x_init()
{
    hi_u8 try_cnt = 0;
	int ret = 0;
	ret = hal_pz_i2c_init(AHT20_I2C_IDX,400000);	
	if(ret != 0){
		return ret ;
	}
    while (HI_ERR_SUCCESS != AHT20_Calibrate()) {
        printf("TQ AHT20 sensor init failed, retry...\r\n");
        hi_udelay(1000);
        if(try_cnt++ > 5){
			ret = -1;
            printf("AHT20 sensor init failed!\r\n");
            break;
        }
    }
	return ret ;
}

float tqs1_aht2x_get_value(hi_u8 type)
{
    float temp = 0;
    float humi = 0;

    AHT20_GetMeasureResult(&temp, &humi);
    if(type == 0)
    {
        return temp;
    }
    else if(type == 1)
    {
        return humi;
    }

    return 0;
}

#else //(BUILD_BOARD == DASHIXIONG_BOARD)

#define AHT20_I2C_IDX HI_I2C_IDX_0

#define AHT20_STARTUP_TIME     20*1000 // 上电启动时间
#define AHT20_CALIBRATION_TIME 40*1000 // 初始化（校准）时间
#define AHT20_MEASURE_TIME     75*1000 // 测量时间

#define AHT20_DEVICE_ADDR   0x38
#define AHT20_READ_ADDR     ((0x38<<1)|0x1)
#define AHT20_WRITE_ADDR    ((0x38<<1)|0x0)

#define AHT20_CMD_CALIBRATION       0xBE // 初始化（校准）命令
#define AHT20_CMD_CALIBRATION_ARG0  0x08
#define AHT20_CMD_CALIBRATION_ARG1  0x00

/**
 * 传感器在采集时需要时间,主机发出测量指令（0xAC）后，延时75毫秒以上再读取转换后的数据并判断返回的状态位是否正常。
 * 若状态比特位[Bit7]为0代表数据可正常读取，为1时传感器为忙状态，主机需要等待数据处理完成。
 **/
#define AHT20_CMD_TRIGGER       0xAC // 触发测量命令
#define AHT20_CMD_TRIGGER_ARG0  0x33
#define AHT20_CMD_TRIGGER_ARG1  0x00

// 用于在无需关闭和再次打开电源的情况下，重新启动传感器系统，软复位所需时间不超过20 毫秒
#define AHT20_CMD_RESET      0xBA // 软复位命令

#define AHT20_CMD_STATUS     0x71 // 获取状态命令

/**
 * STATUS 命令回复：
 * 1. 初始化后触发测量之前，STATUS 只回复 1B 状态值；
 * 2. 触发测量之后，STATUS 回复6B： 1B 状态值 + 2B 湿度 + 4b湿度 + 4b温度 + 2B 温度
 *      RH = Srh / 2^20 * 100%
 *      T  = St  / 2^20 * 200 - 50
 **/
#define AHT20_STATUS_BUSY_SHIFT 7       // bit[7] Busy indication
#define AHT20_STATUS_BUSY_MASK  (0x1<<AHT20_STATUS_BUSY_SHIFT)
#define AHT20_STATUS_BUSY(status) ((status & AHT20_STATUS_BUSY_MASK) >> AHT20_STATUS_BUSY_SHIFT)

#define AHT20_STATUS_MODE_SHIFT 5       // bit[6:5] Mode Status
#define AHT20_STATUS_MODE_MASK  (0x3<<AHT20_STATUS_MODE_SHIFT)
#define AHT20_STATUS_MODE(status) ((status & AHT20_STATUS_MODE_MASK) >> AHT20_STATUS_MODE_SHIFT)

                                        // bit[4] Reserved
#define AHT20_STATUS_CALI_SHIFT 3       // bit[3] CAL Enable
#define AHT20_STATUS_CALI_MASK  (0x1<<AHT20_STATUS_CALI_SHIFT)
#define AHT20_STATUS_CALI(status) ((status & AHT20_STATUS_CALI_MASK) >> AHT20_STATUS_CALI_SHIFT)
                                        // bit[2:0] Reserved

#define AHT20_STATUS_RESPONSE_MAX 6

#define AHT20_RESOLUTION            (1<<20)  // 2^20

#define AHT20_MAX_RETRY 10

static uint32_t AHT20_Read(uint8_t* buffer, uint32_t buffLen)
{
   return hal_pz_i2c_read(HI_I2C_IDX_0,AHT20_DEVICE_ADDR,buffer,buffLen);
}

static uint32_t AHT20_Write(uint8_t* buffer, uint32_t buffLen)
{
    return hal_pz_i2c_write(HI_I2C_IDX_0,AHT20_DEVICE_ADDR,buffer,buffLen);
}

// 发送获取状态命令
static uint32_t AHT20_StatusCommand(void)
{
    uint8_t statusCmd[] = { AHT20_CMD_STATUS };
    return AHT20_Write(statusCmd, sizeof(statusCmd));
}

// 发送软复位命令
static uint32_t AHT20_ResetCommand(void)
{
    uint8_t resetCmd[] = {AHT20_CMD_RESET};
    return AHT20_Write(resetCmd, sizeof(resetCmd));
}

// 发送初始化校准命令
static uint32_t AHT20_CalibrateCommand(void)
{
    uint8_t clibrateCmd[] = {AHT20_CMD_CALIBRATION, AHT20_CMD_CALIBRATION_ARG0, AHT20_CMD_CALIBRATION_ARG1};
    return AHT20_Write(clibrateCmd, sizeof(clibrateCmd));
}

// 读取温湿度值之前， 首先要看状态字的校准使能位Bit[3]是否为 1(通过发送0x71可以获取一个字节的状态字)，
// 如果不为1，要发送0xBE命令(初始化)，此命令参数有两个字节， 第一个字节为0x08，第二个字节为0x00。
uint32_t AHT20_Calibrate(void)
{
    uint32_t retval = 0;
    uint8_t buffer[AHT20_STATUS_RESPONSE_MAX];
    memset(&buffer, 0x0, sizeof(buffer));

    retval = AHT20_StatusCommand();
    if (retval != HI_ERR_SUCCESS) {
        return retval;
    }

    retval = AHT20_Read(buffer, sizeof(buffer));
    if (retval != HI_ERR_SUCCESS) {
        return retval;
    }

    if (AHT20_STATUS_BUSY(buffer[0]) || !AHT20_STATUS_CALI(buffer[0])) {
        retval = AHT20_ResetCommand();
        if (retval != HI_ERR_SUCCESS) {
            return retval;
        }
        usleep(AHT20_STARTUP_TIME);
        retval = AHT20_CalibrateCommand();
        usleep(AHT20_CALIBRATION_TIME);
        return retval;
    }

    return HI_ERR_SUCCESS;
}

// 发送 触发测量 命令，开始测量
uint32_t AHT20_StartMeasure(void)
{
    uint8_t triggerCmd[] = {AHT20_CMD_TRIGGER, AHT20_CMD_TRIGGER_ARG0, AHT20_CMD_TRIGGER_ARG1};
    return AHT20_Write(triggerCmd, sizeof(triggerCmd));
}

// 接收测量结果，拼接转换为标准值
int AHT20_GetMeasureResult(float* temp, float* humi)
{
    uint32_t retval = 0, i = 0;
    if (temp == NULL || humi == NULL) {
        return HI_ERR_FAILURE;
    }

    uint8_t buffer[AHT20_STATUS_RESPONSE_MAX];
    memset(&buffer, 0x0, sizeof(buffer));
    retval = AHT20_Read(buffer, sizeof(buffer));  // recv status command result
    if (retval != HI_ERR_SUCCESS) {
        return retval;
    }

    for (i = 0; AHT20_STATUS_BUSY(buffer[0]) && i < AHT20_MAX_RETRY; i++) {
        // printf("AHT20 device busy, retry %d/%d!\r\n", i, AHT20_MAX_RETRY);
        usleep(AHT20_MEASURE_TIME);
        retval = AHT20_Read(buffer, sizeof(buffer));  // recv status command result
        if (retval != HI_ERR_SUCCESS) {
            return retval;
        }
    }
    if (i >= AHT20_MAX_RETRY) {
        printf("AHT20 device always busy!\r\n");
        return HI_ERR_SUCCESS;
    }

    uint32_t humiRaw = buffer[1];
    humiRaw = (humiRaw << 8) | buffer[2];
    humiRaw = (humiRaw << 4) | ((buffer[3] & 0xF0) >> 4);
    *humi = humiRaw / (float)AHT20_RESOLUTION * 100;

    uint32_t tempRaw = buffer[3] & 0x0F;
    tempRaw = (tempRaw << 8) | buffer[4];
    tempRaw = (tempRaw << 8) | buffer[5];
    *temp = tempRaw / (float)AHT20_RESOLUTION * 200 - 50;
    //printf("humi = %05X, %f, temp= %05X, %f\r\n", humiRaw, *humi, tempRaw, *temp);
    return HI_ERR_SUCCESS;
}


hi_void aht2x_prepare()
{
    hi_u8 try_cnt = 0;
    while (HI_ERR_SUCCESS != AHT20_Calibrate()) {
        printf("AHT20 sensor init failed, retry...\r\n");
        hi_udelay(1000);
        if(try_cnt++ > 5){
            printf("AHT20 sensor init failed!\r\n");
            break;
        }
    }
}

int tqs1_aht2x_init()
{
    hi_u8 try_cnt = 0;
	int ret = 0;
	ret = hal_pz_i2c_init(AHT20_I2C_IDX,400000);	
	if(ret != 0){
		return ret ;
	}
    while (HI_ERR_SUCCESS != AHT20_Calibrate()) {
        printf(" Dshix AHT20 sensor init failed, retry...\r\n");
        hi_udelay(1000);
        if(try_cnt++ > 5){
			ret = -1;
            printf("AHT20 sensor init failed!\r\n");
            break;
        }
    }
	return ret ;
}

float tqs1_aht2x_get_value(hi_u8 type)
{
    float temp = 0;
    float humi = 0;
	int ret1 = AHT20_StartMeasure();
    int ret = AHT20_GetMeasureResult(&temp, &humi);
	if(ret == HI_ERR_SUCCESS && ret1 == HI_ERR_SUCCESS){
	    if(type == 0)
	    {
	        return temp;
	    }
	    else if(type == 1)
	    {
	        return humi;
	    }
	}
    return 0;
}



#endif


