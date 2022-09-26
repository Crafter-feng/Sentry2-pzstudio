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





#ifndef SYS_DEBUG_UART_H
#define SYS_DEBUG_UART_H

#include <unistd.h> 
#include "cmsis_os2.h" 
#include "iot_gpio.h" 
#include "iot_uart.h" 
#include "hi_io.h"
#include "sys_debug.h"

#if SYS_DEBUG_ENABLE==1
void Sys_Debug_Uart_Init(int baud) ;
void Sys_Debug_Uart_DeInit(void);
int Sys_Debug_Uart_Send(uint8_t*data,uint32_t len);
int Sys_Debug_Uart_Recv(uint8_t *data,uint32_t len);
int Sys_Debug_Uart_Putchar(char ch);
#endif


#endif



