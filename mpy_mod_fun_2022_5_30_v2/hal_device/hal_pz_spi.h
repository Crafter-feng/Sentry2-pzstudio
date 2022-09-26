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




#ifndef HAL_PZ_I2C_H
#define HAL_PZ_I2C_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <hi_types_base.h>
#include <hi_early_debug.h>
#include <hi_stdlib.h>
#include <hi_errno.h>
#include <hi_i2c.h>
#include <hi_io.h>
#include <unistd.h>
#include "iot_gpio.h" 
#include "iot_errno.h"
#include "iot_i2c.h" 
#include "hi_io.h"
#include "los_mux.h"
#include "cmsis_os2.h" 


typedef struct _hal_pz_i2c_t{
	/* 设备初始化的次数 */
	int16_t cnt;
	/* 读互斥锁 */
	UINT32 Mux;
	unsigned int baudrate;
}hal_pz_i2c_t;


int hal_pz_i2c_init(hi_i2c_idx id,unsigned int baudrate);
int hal_pz_i2c_deinit(int id);
int hal_pz_i2c_read(unsigned int id, unsigned short deviceAddr, unsigned char *data, unsigned int dataLen);
int hal_pz_i2c_write(unsigned int id, unsigned short deviceAddr, const unsigned char *data, unsigned int dataLen);



#endif


