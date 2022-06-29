#ifndef SYS_DEBUG_H
#define SYS_DEBUG_H
#include <stdio.h>
#include <stdarg.h>

#define SYS_DEBUG_ENABLE 0
#include "sys_debug_uart.h"



#if SYS_DEBUG_ENABLE == 1

#define console_print  Sys_Debug_Uart_Putchar 
 
 
#define  MAX_NUMBER_BYTES  128
 
extern int my_printf_test(void);
int sys_printf(const char *fmt, ...) ;
void Sys_Debug_Init(void);

#define PZ_SYS_DEBUG(...)    sys_printf(__VA_ARGS__)
#else

#define PZ_SYS_DEBUG(...)  
void Sys_Debug_Init(void);

#endif

//ESP_LOGI


#endif

