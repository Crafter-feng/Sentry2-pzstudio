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

#ifndef INC_ICM_H_
#define INC_ICM_H_
#if BUILD_BOARD == DASHIXIONG_BOARD
/* i2c封装层已经做了移位，这里直接填写地址即可 */

#define ICM_READ_ADDR     ((0x68)) 
#define ICM_WRITE_ADDR    ((0x68))
#define power_mgmt 			0x4E
#define DEVICE_CONFIG		0x11
#define DRIVE_CONFIG 		0x13
#define who_am_i			0x75
#define temp_data1			0x1D
#define temp_data0			0x1E
#define GYRO_CONFIG0		0x4F
#define ACCEL_CONFIG0		0x50
#define GYRO_CONFIG1		0x51
#define GYRO_ACCEL_CONFIG0	0x52
#define ACCEL_CONFIG1		0x53
#define XA_ST_DATA			0x3B
#define YA_ST_DATA			0x3C
#define ZA_ST_DATA			0x3D
#define BANK_SEL			0x76


#define ACCEL_DATA_X1		0x1F
#define ACCEL_DATA_X0		0x20

#define ACCEL_DATA_Y1		0x21
#define ACCEL_DATA_Y0		0x22

#define ACCEL_DATA_Z1		0x23
#define ACCEL_DATA_Z0		0x24

#define GYRO_DATA_X1		0x25
#define GYRO_DATA_X0		0x26

#define GYRO_DATA_Y1		0x27
#define GYRO_DATA_Y0		0x28

#define GYRO_DATA_Z1		0x29
#define GYRO_DATA_Z0		0x2A

#define FIFO_CONFIG_INIT	0x16
#define FIFO_CONFIGURATION	0x5F
#define FIFO_DATA_REG		0x30

#define WIFI_IOT_I2C_IDX_0 0



int icm_initialize();
int read_values(uint8_t *data);

#endif

#endif /* INC_ICM_H_ */