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
 
 
 
#ifndef MICROPY_INCLUDED_MACHINE_UART_H
#define MICROPY_INCLUDED_MACHINE_UART_H

#include "py/obj.h"
#include "py/mphal.h"


typedef struct _machine_uart_obj_t {
    mp_obj_base_t base;
	/* 串口号 */
    int8_t uart_num;
	/* 波特率 */
	uint32_t baudrate;
	/* 数据位 */
    uint8_t bits;
	/* 校验位 */
    uint8_t parity;
	/* 停止位 */
    uint8_t stop;
	/*  */
    uint16_t timeout;
} machine_uart_obj_t;


#endif // MICROPY_INCLUDED_MACHINE_UART_H
