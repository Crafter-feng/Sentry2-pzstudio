/*
 * Copyright (C) 2022 Polygon Zone Open Source Organization .
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http:// www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 *
 * limitations under the License.
 */
 
 
 
 
 
 
#include <string.h>
#include <unistd.h>
#include "cmsis_os2.h"

#include "iot_errno.h"
#include "iot_i2c.h"

#include "icm.h"
#include "ohos_types.h"
#include "hal_pz_i2c.h"
#if BUILD_BOARD == DASHIXIONG_BOARD

uint8_t  device_address = 0x68;




unsigned char fifo_data[17];


int icm_initialize(){
	unsigned char configure_reset = 0x01;
	unsigned char fifo_conf_data = 0x03;
	unsigned char buffer = 0x1F; //  temperature sensor enabled. RC oscillator is on, gyro and accelerometer low noise mode,
	unsigned char fifo_init = 0x40;
	
	uint32 status = 0;
	uint8 sendUserRSTCmd [] = {DEVICE_CONFIG, configure_reset};
	uint8 sendUserPowerCmd [] = {power_mgmt, buffer};
	uint8 sendUserFIFOInitCmd [] = {FIFO_CONFIG_INIT, fifo_init};
	uint8 sendUserFIFOCfgCmd [] = {FIFO_CONFIGURATION, fifo_conf_data};
	
	hal_pz_i2c_init(0,400000);
	
	status = hal_pz_i2c_write(0, device_address, sendUserRSTCmd, sizeof(sendUserRSTCmd));
	osDelay(10);
	if (status != IOT_SUCCESS) {
		return -1;
	}
	
	// HAL_I2C_Mem_Write(&hi2c1, device_address, power_mgmt, 1, &buffer, 1, 100);
	status = hal_pz_i2c_write(0, device_address, sendUserPowerCmd, sizeof(sendUserPowerCmd));
	osDelay(10);
	if (status != IOT_SUCCESS) {
		return -1;
	}
	
	// HAL_I2C_Mem_Write(&hi2c1, device_address, FIFO_CONFIG_INIT, 1, &fifo_init, 1, 100);
	status = hal_pz_i2c_write(0, device_address, sendUserFIFOInitCmd, sizeof(sendUserFIFOInitCmd));
	osDelay(10);

	if (status != IOT_SUCCESS) {
			return -1;
	}

	// HAL_I2C_Mem_Write(&hi2c1, device_address, FIFO_CONFIGURATION, 1, &fifo_conf_data, 1, 100);
	status = hal_pz_i2c_write(0, device_address, sendUserFIFOCfgCmd, sizeof(sendUserFIFOCfgCmd));
	osDelay(10);
	if (status != IOT_SUCCESS) {
		return -1;
	}
	return 0;
}


int read_values(uint8_t *data){
	uint32 status = 0;
	uint8 ReadFIFODataCmd [] = {FIFO_DATA_REG};
	if(data == NULL){
		return -1;
	}
	status = hal_pz_i2c_write(0, device_address, ReadFIFODataCmd, sizeof(ReadFIFODataCmd));
	osDelay(10);

	if (status != IOT_SUCCESS) {
        return -1;
	}
	

	status = hal_pz_i2c_read(0,device_address, fifo_data, sizeof(fifo_data));
	if (status != IOT_SUCCESS){
		return -1;
	}
	memcpy(data,fifo_data,12);
	return 0;
}
#endif
