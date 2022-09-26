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



#ifndef HAL_PZ_UART_H
#define HAL_PZ_UART_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <hi_types_base.h>
#include <hi_early_debug.h>
#include <hi_stdlib.h>
#include <hi_errno.h>
#include <hi_uart.h>
#include <hi_io.h>
#include <unistd.h>
#include "iot_gpio.h" 
#include "iot_errno.h"
#include "iot_uart.h" 
#include "hi_io.h"
#include "los_mux.h"
#include "cmsis_os2.h" 



typedef struct _hal_pz_uart_t{
	/* 设备初始化的次数 */
	uint16_t cnt;
	/* 读互斥锁 */
	UINT32 rx_Mux;
	/* 写互斥锁 */
	UINT32 tx_Mux;
	
}hal_pz_uart_t;


int hal_pz_uart_init(int uart_num,IotUartAttribute *uart_cfg);
int hal_pz_uart_deinit(int uart_num);
int hal_pz_uart_len(int uart_num);
int hal_pz_uart_write(hi_uart_idx uart_num, const hi_u8 *data, hi_u32 data_len);
int hal_pz_uart_read(hi_uart_idx uart_num, hi_u8 *data, hi_u32 data_len);
int hal_pz_uart_read_timeout(hi_uart_idx uart_num, hi_u8 *data, hi_u32 len, hi_u32 timeout_ms);


#endif



