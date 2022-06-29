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



