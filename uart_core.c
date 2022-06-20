#include <unistd.h>
#include "py/mpconfig.h"
#include "los_mux.h"
/*
 * Core UART functions to implement for a port
 */

#if MICROPY_MIN_USE_STM32_MCU
typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
} periph_uart_t;
#define USART1 ((periph_uart_t *)0x40011000)
#endif
// UINT32 g_testMux;
extern UINT32 uartMux;
extern unsigned int write_bufIndex;
extern unsigned char sharedUartReadBuff[4096];
extern unsigned int write_uartIndex;
extern unsigned int writeLen;
extern unsigned char sharedUartWriteBuff[4096];
// Receive single character
int mp_hal_stdin_rx_chr(void) {
    // if (g_testMux == NULL){
    //     LOS_MuxCreate(&g_testMux);
    // }
    // unsigned int len = 0; 
    // unsigned char uartReadBuff[1] = {0};
    // unsigned char c = 0;
    // LOS_MuxPend(g_testMux, LOS_WAIT_FOREVER);
    // len = IoTUartRead(0, uartReadBuff, 1);
    
    // LOS_MuxPost(&g_testMux);
    // c = uartReadBuff[0];
    unsigned char c = 0;
    LOS_MuxPend(uartMux, LOS_WAIT_FOREVER);
    if(write_bufIndex > 0){
        c = sharedUartReadBuff[0];
        for(int i=0;i<write_bufIndex;i++){
            sharedUartReadBuff[i] = sharedUartReadBuff[i+1];
        }
        write_bufIndex = write_bufIndex - 1;
    }
    LOS_MuxPost(uartMux);
    usleep(100); 
    return c;
}

// Send string of given length
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    
    // if (g_testMux == NULL){
    //     LOS_MuxCreate(&g_testMux);
    // }
    // LOS_MuxPend(g_testMux, LOS_WAIT_FOREVER);
    // IoTUartWrite(0, (unsigned char *)str, len);
    // LOS_MuxPost(&g_testMux);
    // printf("before lock");
    LOS_MuxPend(uartMux, LOS_WAIT_FOREVER);
    // printf("%s writelen1 = %d\n",str,len);
    for(int i = write_uartIndex; i < len + write_uartIndex; i++){
        sharedUartWriteBuff[i] = str[i-write_uartIndex];
    }
    writeLen = writeLen + len;
    write_uartIndex = write_uartIndex + len;
    // printf("writelen2 = %d\n",writeLen);
    LOS_MuxPost(uartMux);
    usleep(100); 
}
