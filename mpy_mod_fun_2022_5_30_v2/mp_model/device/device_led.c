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



#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <hi_types_base.h>
#include <hi_early_debug.h>
#include <hi_stdlib.h>
#include <hi_errno.h>
#include <hi_uart.h>
#include <hi_io.h>
#include "iot_gpio.h" 
#include "iot_uart.h" 
#include "hi_io.h"
#include "hi_gpio.h"
#include "iot_gpio.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/stream.h"
#include "py/mperrno.h"
#include "moddevice.h"
#include "parse_pin.h"

#if BUILD_BOARD == DASHIXIONG_BOARD


typedef struct _device_led_obj_t {
    mp_obj_base_t base;
	uint8_t id;
	uint8_t pin;
} device_led_obj_t;



MP_STATIC mp_obj_t device_led_obj_init_helper(device_led_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    IoTGpioInit(self->pin);
	if(self->pin == HI_GPIO_IDX_7){
		hi_io_set_func(self->pin,HI_IO_FUNC_GPIO_7_GPIO);
	}else if(self->pin == HI_GPIO_IDX_2){
		hi_io_set_func(self->pin,HI_IO_FUNC_GPIO_2_GPIO);
	}
	IoTGpioSetDir(self->pin,IOT_GPIO_DIR_OUT);
	IoTGpioSetOutputVal(self->pin,0);
    return mp_const_none;
}











// pin.init(mode, pull)
MP_STATIC mp_obj_t device_led_obj_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
	
	return device_led_obj_init_helper(args[0], n_args - 1, args + 1, kw_args);
}
MP_DEFINE_CONST_FUN_OBJ_KW(device_led_init_obj, 1, device_led_obj_init);



//(mp_obj_t self_in, size_t n_args, size_t n_kw, const mp_obj_t *args)
MP_STATIC mp_obj_t device_led_value(size_t n_args, const mp_obj_t *args) {
	mp_arg_check_num(n_args - 1, 0, 0, 1, args + 1);
    device_led_obj_t *self = args[0];
	IotGpioValue val;
    if (n_args == 1) {
		IoTGpioGetOutputVal(self->pin,&val);
    	return MP_OBJ_NEW_SMALL_INT(val);
    } else if(n_args>=2){
        IoTGpioSetOutputVal(self->pin, mp_obj_is_true(args[1]));
        return mp_const_none;
    }
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(device_led_value_obj, 1, 2, device_led_value);






MP_STATIC mp_obj_t device_led_off(mp_obj_t self_in) {
    device_led_obj_t *self = MP_OBJ_TO_PTR(self_in);
    IoTGpioSetOutputVal(self->pin, 0);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(device_led_off_obj, device_led_off);





MP_STATIC mp_obj_t device_led_on(mp_obj_t self_in) {
    device_led_obj_t *self = MP_OBJ_TO_PTR(self_in);
    IoTGpioSetOutputVal(self->pin, 1);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(device_led_on_obj, device_led_on);






MP_STATIC void device_led_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    device_led_obj_t *self = self_in;
    mp_printf(print, "LED(%u)", self->id);
}






mp_obj_t mp_led_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 1, 1, true);
    int led_num = mp_obj_get_int(args[0]);
    device_led_obj_t *self = m_new_obj(device_led_obj_t);
	memset(self,0,sizeof(device_led_obj_t));
	self->base.type = &device_led_type;
	self->id = led_num;
	if(self->id==0){
		self->pin=HI_GPIO_IDX_7;
	}else if(self->id==1){
		self->pin=HI_GPIO_IDX_2;
	}else{
		mp_raise_ValueError(MP_ERROR_TEXT("invalid led"));
	}

    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    device_led_obj_init_helper(self, n_args - 1, args + 1, &kw_args);
    return MP_OBJ_FROM_PTR(self);
}







MP_STATIC const mp_rom_map_elem_t device_led_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&device_led_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_value), MP_ROM_PTR(&device_led_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_off), MP_ROM_PTR(&device_led_off_obj) },
    { MP_ROM_QSTR(MP_QSTR_on), MP_ROM_PTR(&device_led_on_obj) },
};




MP_STATIC MP_DEFINE_CONST_DICT(device_led_locals_dict, device_led_locals_dict_table);

const mp_obj_type_t device_led_type = {
    { &mp_type_type },
    .name = MP_QSTR_LED,
    .print = device_led_print,
    .make_new = mp_led_make_new,
    .locals_dict = (mp_obj_dict_t *)&device_led_locals_dict,
};


#else if BUILD_BOARD == TQ_BOARD
#include "hi_spi.h"


static unsigned char ledData[3][3]={0};

typedef struct _device_led_obj_t {
    mp_obj_base_t base;
	uint8_t id;
} device_led_obj_t;

int color_led_set_color(unsigned char val[][3], unsigned char led_num)
{
    hi_spi_deinit(HI_SPI_ID_0);
    hi_spi_cfg_basic_info spi_cfg_basic_info;
    spi_cfg_basic_info.cpha = 1;
    spi_cfg_basic_info.cpol = 1;
    spi_cfg_basic_info.data_width = HI_SPI_CFG_DATA_WIDTH_E_8BIT;
    spi_cfg_basic_info.endian = 0;
    spi_cfg_basic_info.fram_mode = 0;
    spi_cfg_basic_info.freq = 6400000; /* set frequency 2000000 */
    hi_spi_cfg_init_param spi_init_param = {0};
    spi_init_param.is_slave = HI_FALSE;
	IoTGpioInit(HI_IO_NAME_GPIO_5);
	IoTGpioInit(HI_IO_NAME_GPIO_9);
	IoTGpioInit(HI_IO_NAME_GPIO_10);
	IoTGpioInit(HI_IO_NAME_GPIO_7);
    hi_io_set_func(HI_IO_NAME_GPIO_5, HI_IO_FUNC_GPIO_5_SPI0_CSN);
    hi_io_set_func(HI_IO_NAME_GPIO_9, HI_IO_FUNC_GPIO_9_SPI0_TXD);
    hi_io_set_func(HI_IO_NAME_GPIO_10, HI_IO_FUNC_GPIO_10_SPI0_CK);
    hi_io_set_func(HI_IO_NAME_GPIO_7, HI_IO_FUNC_GPIO_7_SPI0_RXD);
    int ret = hi_spi_init(HI_SPI_ID_0, spi_init_param, &spi_cfg_basic_info);
    if (ret != HI_ERR_SUCCESS) {
        return -1;
    } 
    //display
    char spiData[16*3*8]={0};
    for(int num=0; num<led_num; num++)
    {
        for(int i=0; i<3;i++)
        {
            for(int j=7; j>=0; j--)
            {
                int bytetmp = ((val[num][i]>>j) & 0x01);
                if(bytetmp == 1)
                {
                    spiData[num*24+i*8+(7-j)] = 0b11111100;
                }
                else
                {
                    spiData[num*24+i*8+(7-j)] = 0b11000000;
                }
                
            }
        }
    }
    hi_spi_host_write(HI_SPI_ID_0, spiData, led_num*24);
    //reset
    char dataReset = 0b00000000;
    hi_spi_host_write(HI_SPI_ID_0, &dataReset, 1);
    usleep(100);
    hi_spi_deinit(HI_SPI_ID_0);
    return 0;
}


MP_STATIC mp_obj_t device_led_obj_init_helper(device_led_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    ledData[(self->id-1)%3][0] = 0x00;
	ledData[(self->id-1)%3][1] = 0x00;
	ledData[(self->id-1)%3][2] = 0x00;
	color_led_set_color(ledData,3);
    return mp_const_none;
}











// pin.init(mode, pull)
MP_STATIC mp_obj_t device_led_obj_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
	
	return device_led_obj_init_helper(args[0], n_args - 1, args + 1, kw_args);
}
MP_DEFINE_CONST_FUN_OBJ_KW(device_led_init_obj, 1, device_led_obj_init);



//(mp_obj_t self_in, size_t n_args, size_t n_kw, const mp_obj_t *args)
MP_STATIC mp_obj_t device_led_value(size_t n_args, const mp_obj_t *args) {
	mp_arg_check_num(n_args - 1, 0, 0, 1, args + 1);
    device_led_obj_t *self = args[0];
	IotGpioValue val;
    if (n_args == 1) {
		/* 获取值 */
		mp_obj_t tuple[3];
		tuple[2] = mp_obj_new_int(ledData[(self->id-1)%3][1]);
    	tuple[1] = mp_obj_new_int(ledData[(self->id-1)%3][0]);
		tuple[0] = mp_obj_new_int(ledData[(self->id-1)%3][2]);
    	return mp_obj_new_tuple(3, tuple);
    } else if(n_args>=2) {
        /* 设置值 */
		uint32_t color = mp_obj_get_int_truncated(args[1]);
		ledData[(self->id-1)%3][1] = (color >> 16) & 0xFF;
		ledData[(self->id-1)%3][0] = (color >> 8)  & 0xFF;
		ledData[(self->id-1)%3][2] = (color >> 0)  & 0xFF;
		color_led_set_color(ledData,3);
        return mp_const_none;
    }
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(device_led_value_obj, 1, 2, device_led_value);




MP_STATIC mp_obj_t device_led_set_color(size_t n_args, const mp_obj_t *args) {
	
    device_led_obj_t *self = args[0];
	uint8_t r_color = mp_obj_get_int_truncated(args[1]);
	uint8_t g_color = mp_obj_get_int_truncated(args[2]);
	uint8_t b_color = mp_obj_get_int_truncated(args[3]);
	ledData[(self->id-1)%3][1] = r_color;
	ledData[(self->id-1)%3][0] = g_color;
	ledData[(self->id-1)%3][2] = b_color;
	color_led_set_color(ledData,3);
	return  mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(device_led_set_color_obj, 4, 4, device_led_set_color);





MP_STATIC void device_led_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    device_led_obj_t *self = self_in;
    mp_printf(print, "LED(%u)", self->id);
}






mp_obj_t mp_led_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 1, 1, true);
    int led_num = mp_obj_get_int(args[0]);
	if(led_num<0 || 3<led_num){
		mp_raise_ValueError(MP_ERROR_TEXT("invalid led"));
	}
	device_led_obj_t *self = m_new_obj(device_led_obj_t);
	memset(self,0,sizeof(device_led_obj_t));
	self->base.type = &device_led_type;
	self->id = led_num;
    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    device_led_obj_init_helper(self, n_args - 1, args + 1, &kw_args);
    return MP_OBJ_FROM_PTR(self);
}


MP_STATIC const mp_rom_map_elem_t device_led_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&device_led_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_value), MP_ROM_PTR(&device_led_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_color), MP_ROM_PTR(&device_led_set_color_obj) },
};

MP_STATIC MP_DEFINE_CONST_DICT(device_led_locals_dict, device_led_locals_dict_table);


const mp_obj_type_t device_led_type = {
    { &mp_type_type },
    .name = MP_QSTR_LED,
    .print = device_led_print,
    .make_new = mp_led_make_new,
    .locals_dict = (mp_obj_dict_t *)&device_led_locals_dict,
};



#endif








