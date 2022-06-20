#ifndef __SC7A20_H__
#define __SC7A20_H__

#include <hi_types_base.h>
#include <hi_i2c.h>
#include <hi_early_debug.h>
#include <hi_stdlib.h>

#if BUILD_BOARD == TQ_BOARD

/*
#include <hi_types_base.h>
#include <hi_early_debug.h>
#include <hi_stdlib.h>
#include <hi_errno.h>
#include <hi_uart.h>
#include <hi_io.h>
#include <hi_i2c.h>


hi_void set_uart_baudrate(hi_u32 baudrate);
hi_void write_uart_string(char *str);
hi_void write_uart_hex(hi_u8 *data, hi_u8 data_len);
hi_u8 *read_uart_data(hi_void);
*/


//#define APDS9960_I2C_ADDR       0x39
//#define AHT20_READ_ADDR     ((APDS9960_I2C_ADDR<<1)|0x1)
//#define AHT20_WRITE_ADDR    ((APDS9960_I2C_ADDR<<1)|0x0)
#define SC7A20_I2C_IDX HI_I2C_IDX_1

#define SC7A20_I2C_ADDR  0x18
#define SC7A20_I2C_WADDR 0x30	//I2C写地址：7位I2C地址+一位写
#define SC7A20_I2C_RADDR 0x31	//I2C写地址：7位I2C地址+一位读

hi_u8 SC7A20_Init();
hi_s32  SC7A20_Get_ACCD(hi_u8 accd_lsb,hi_u8 accd_msb);
hi_s32 * SC7A20_GetInfo();
hi_s32 motion(hi_void);

hi_s32 get_x(hi_void);
hi_s32 get_y(hi_void);
hi_s32 get_z(hi_void);
#endif
#endif

