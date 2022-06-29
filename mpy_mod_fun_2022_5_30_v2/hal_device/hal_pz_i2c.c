#include "hal_pz_i2c.h"


static hal_pz_i2c_t pz_i2c_ctrl[HI_I2C_IDX_1+1];



int hal_pz_i2c_init(hi_i2c_idx id,unsigned int baudrate){
	int ret = IOT_FAILURE;
	if(id<0 || (id>=(HI_I2C_IDX_1+1))){
		return IOT_FAILURE;
	}else{
		if(pz_i2c_ctrl[id].cnt==0){
			IoTI2cDeinit(id);
			if(id == HI_I2C_IDX_0){
				hi_io_set_func(13,0);
				hi_io_set_func(14,0);
				IoTGpioDeinit(13);
				IoTGpioDeinit(14);
				IoTGpioInit(13);
		    	hi_io_set_func(13, HI_IO_FUNC_GPIO_13_I2C0_SDA);
		    	IoTGpioInit(14);    
		    	hi_io_set_func(14, HI_IO_FUNC_GPIO_14_I2C0_SCL);
			}else if(id == HI_I2C_IDX_1){
				hi_io_set_func(0,0);
				hi_io_set_func(1,0);
				IoTGpioDeinit(0);
				IoTGpioDeinit(1);
				IoTGpioInit(0);
	    		hi_io_set_func(0, HI_IO_FUNC_GPIO_0_I2C1_SDA);
	    		IoTGpioInit(1);    
	    		hi_io_set_func(1, HI_IO_FUNC_GPIO_1_I2C1_SCL);
			}
			ret = IoTI2cInit(id, baudrate);
			if(ret == IOT_SUCCESS){
				/* 创建互斥锁 */
				int ret1=LOS_OK;
				if(pz_i2c_ctrl[id].cnt==0){
					ret1 = LOS_MuxCreate(&(pz_i2c_ctrl[id].Mux));
				}
				if(ret1==LOS_OK ){
					pz_i2c_ctrl[id].cnt++;
					pz_i2c_ctrl[id].baudrate = baudrate;
				}else{
					return IOT_FAILURE;
				}
			}
		}else{
			if(pz_i2c_ctrl[id].baudrate != baudrate){
				IoTI2cSetBaudrate(id,baudrate);
				pz_i2c_ctrl[id].baudrate = baudrate;
			}
			ret = IOT_SUCCESS;
		}
	}
	return ret;
}






int hal_pz_i2c_deinit(int id){
	if(id<0 || (id>=(HI_I2C_IDX_1+1))){
		return IOT_FAILURE;
	}else{
		if(pz_i2c_ctrl[id].cnt==1){
			LOS_MuxDelete(pz_i2c_ctrl[id].Mux);
			pz_i2c_ctrl[id].Mux = 0;
			IoTI2cDeinit(id);
			if(id == HI_I2C_IDX_1){
				hi_io_set_func(0,0);    //使能引脚0、1的的UART1复用功能
				hi_io_set_func(1,0);
				IoTGpioDeinit(0);//使用GPIO，需要调用该接口 
				IoTGpioDeinit(1);//使用GPIO，需要调用该接口
			}else if(id == HI_I2C_IDX_0){
				hi_io_set_func(13,0);
				hi_io_set_func(14,0);
				IoTGpioDeinit(13);
				IoTGpioDeinit(14);
			}
			pz_i2c_ctrl[id].cnt--;
		}else{
			if(pz_i2c_ctrl[id].cnt!=0){
				pz_i2c_ctrl[id].cnt--;
			}else{
				return IOT_FAILURE;
			}
		}
	}
	return IOT_SUCCESS;
}






int hal_pz_i2c_write(unsigned int id, unsigned short deviceAddr, const unsigned char *data, unsigned int dataLen){
	if(id<0 || (id>=(HI_I2C_IDX_1+1))){
		return IOT_FAILURE;
	}
	int ret = 0;
	LOS_MuxPend(pz_i2c_ctrl[id].Mux, LOS_WAIT_FOREVER);
	ret = IoTI2cWrite(id,(deviceAddr<<1),data,dataLen);
	LOS_MuxPost(pz_i2c_ctrl[id].Mux);
	return ret;
}






int hal_pz_i2c_read(unsigned int id, unsigned short deviceAddr, unsigned char *data, unsigned int dataLen){
	if(id<0 || (id>=(HI_I2C_IDX_1+1))){
		return IOT_FAILURE;
	}
	int ret = 0;
	LOS_MuxPend(pz_i2c_ctrl[id].Mux, LOS_WAIT_FOREVER);
	ret = IoTI2cRead(id,(deviceAddr<<1),data,dataLen);
	LOS_MuxPost(pz_i2c_ctrl[id].Mux);
	return ret;
}









