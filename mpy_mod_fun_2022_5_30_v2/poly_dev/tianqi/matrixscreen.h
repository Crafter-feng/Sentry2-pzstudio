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



#ifndef __MATRIXSCREEN_H__
#define __MATRIXSCREEN_H__
/*
#include <hi_types_base.h>

#include <hi_i2c.h>
#include <hi_early_debug.h>
#include <hi_stdlib.h>
#include <hi_stdlib.h>
#include <hi_errno.h>
#include <hi_gpio.h>
#include <hi_pwm.h>
#include <hi_adc.h>
#include <hi_io.h>

//#include "parse_pin.h"
*/
#if 1
//#include "lite_sensor.h"
#include <hi_types_base.h>
#include <hi_i2c.h>
#include <hi_early_debug.h>
#include <hi_stdlib.h>
#include "iot_gpio.h"
#include "iot_i2c.h"
#include "iot_errno.h"
#include "cmsis_os2.h" 


#if 0

typedef struct {

	/* 管理LED灯,每一个位是一个LED灯 */
	uint8_t led_row[8];
	/* 备份显示的字符,即将显示的字符 */
	uint8_t  character[8];
	/* 需要显示的字符点阵 */
	uint8_t *led_mux_buf;
	/* 显示字符的长度 */
	int led_mux_buf_len;
	/* 滚动计数，每滚动完一个字符即八个位则需要更新一个字符 */
	uint8_t roll_cnt;
	/* 滚动字符计数，显示第几个字符 */
	int roll_character_cnt;
	/* 滚动标志 */
	int roll_flag;
	/* 信号量 */
	UINT32 led_matrix_mutex; 
	/* 字体滑动任务 */
	TaskHandle_t  led_matrix_handle;
}Led_Matrix_t;
#endif


extern hi_u8 screen_array_state[8];
hi_void Write_Max7219_byte(hi_u8 DATA);
hi_void Write_Max7219(hi_u8 address,hi_u8 dat);
hi_void Init_MAX7219(hi_u8 din_num,hi_u8 cs_num,hi_u8 clk_num);//14-9-10
hi_void matritest(hi_void);

hi_void matridisplay(hi_u8 *array_date);
hi_void matriOffall();

hi_void matriEnable(hi_bool flag);
hi_void matribrightness(hi_u8 brightness);
hi_void matriWriteChar(hi_u8 c);
hi_void matriShowPic(hi_u8 index);
hi_void matriShowdotMatrix(hi_u8 matrix[7]);
hi_void matriWriteString(hi_u8 *str_date);
hi_u8* getMatrixDate(void);

hi_void matriFilldisplay(hi_u32 array_date0,hi_u32 array_date1);
#endif
#endif
