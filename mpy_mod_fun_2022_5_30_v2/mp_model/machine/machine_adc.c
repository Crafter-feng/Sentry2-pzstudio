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
#include "modmachine.h"
#include "parse_pin.h"
#include "cmsis_os2.h" 
#include "hi_adc.h"


typedef struct _madc_obj_t {
    mp_obj_base_t base;
    int8_t id;
    hi_adc_channel_index adc_ch;
} madc_obj_t;




MP_STATIC mp_obj_t madc_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw,
    const mp_obj_t *args) {
    int wanted_pin = mp_obj_get_int(args[0]);
	 /* 获取映射管脚 */
	s_pin parse_pin = parse_single_pin(wanted_pin);
    if (parse_pin.gpio_aux.gpio_id == HI_GPIO_IDX_MAX) {
        mp_raise_ValueError(MP_ERROR_TEXT("invalid pin"));
    }
	/* 判断该管脚是否是ADC通道 */
	if(parse_pin.adc_ch == HI_ADC_CHANNEL_BUTT){
		mp_raise_ValueError(MP_ERROR_TEXT("invalid Pin for ADC"));
	}
	
	/*  */
	madc_obj_t *self = m_new_obj(madc_obj_t);
	self->base.type = &machine_adc_type;
	self->adc_ch = parse_pin.adc_ch;
	self->id = wanted_pin;
    return MP_OBJ_FROM_PTR(self);
}




MP_STATIC void madc_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    madc_obj_t *self = self_in;
    mp_printf(print, "ADC(Pin(%u))", self->id);
}




// read_analog()
MP_STATIC mp_obj_t madc_analog(mp_obj_t self_in) {
    madc_obj_t *self = MP_OBJ_TO_PTR(self_in);
	unsigned short data = 0;
    int val = hi_adc_read(self->adc_ch,&data,HI_ADC_EQU_MODEL_4,HI_ADC_CUR_BAIS_AUTO,0);
	if (val == -1) {
        mp_raise_ValueError(MP_ERROR_TEXT("parameter error"));
    }
	return MP_OBJ_NEW_SMALL_INT(data);
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(madc_analog_obj, madc_analog);




// read_voltage()
MP_STATIC mp_obj_t madc_voltage(mp_obj_t self_in) {
    madc_obj_t *self = self_in;
	unsigned short data = 0;
    int val = hi_adc_read(self->adc_ch,&data,HI_ADC_EQU_MODEL_4,HI_ADC_CUR_BAIS_AUTO,0);
	if (val == -1) {
        mp_raise_ValueError(MP_ERROR_TEXT("parameter error"));
    }
	float voltage =  hi_adc_convert_to_voltage(data);
	
    return mp_obj_new_float(voltage);
}
MP_DEFINE_CONST_FUN_OBJ_1(madc_voltage_obj, madc_voltage);





MP_STATIC const mp_rom_map_elem_t madc_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_read), MP_ROM_PTR(&madc_analog_obj) },
    { MP_ROM_QSTR(MP_QSTR_voltage), MP_ROM_PTR(&madc_voltage_obj) },
};


MP_STATIC MP_DEFINE_CONST_DICT(madc_locals_dict, madc_locals_dict_table);
const mp_obj_type_t machine_adc_type = {
    { &mp_type_type },
    .name = MP_QSTR_ADC,
    .print = madc_print,
    .make_new = madc_make_new,
    .locals_dict = (mp_obj_t)&madc_locals_dict,
};



