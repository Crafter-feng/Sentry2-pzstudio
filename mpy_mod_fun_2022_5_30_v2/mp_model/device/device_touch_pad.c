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


#if BUILD_BOARD == TQ_BOARD




typedef struct _device_th_pad_obj_t {
    mp_obj_base_t base;
	uint8_t pin;
} device_th_pad_obj_t;



MP_STATIC mp_obj_t device_th_pad_obj_init_helper(device_th_pad_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    IoTGpioInit(self->pin);
	hi_io_set_func(self->pin, HI_IO_FUNC_GPIO_2_GPIO);
	hi_io_set_pull(self->pin, HI_IO_PULL_DOWN);
	IoTGpioSetDir(self->pin,  IOT_GPIO_DIR_IN);
    return mp_const_none;
}





MP_STATIC mp_obj_t device_th_pad_obj_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
	return device_th_pad_obj_init_helper(args[0], n_args - 1, args + 1, kw_args);
}
MP_DEFINE_CONST_FUN_OBJ_KW(device_th_pad_init_obj, 1, device_th_pad_obj_init);






MP_STATIC mp_obj_t device_th_pad_value(size_t n_args, const mp_obj_t *args) {
    device_th_pad_obj_t *self = args[0];
	IotGpioValue val;
	IoTGpioGetInputVal(self->pin,&val);
	return MP_OBJ_NEW_SMALL_INT(val);
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(device_th_pad_value_obj, 1, 1, device_th_pad_value);





MP_STATIC void device_th_pad_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    device_th_pad_obj_t *self = self_in;
    mp_printf(print, "TOUCH PAD(%u)");
}





mp_obj_t mp_th_pad_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 0, 0, true);
    device_th_pad_obj_t *self = m_new_obj(device_th_pad_obj_t);
	memset(self,0,sizeof(device_th_pad_obj_t));
	self->base.type = &device_touch_pad_type;
	self->pin=HI_GPIO_IDX_2;
	
    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    device_th_pad_obj_init_helper(self, n_args - 1, args + 1, &kw_args);
    return MP_OBJ_FROM_PTR(self);
}




MP_STATIC const mp_rom_map_elem_t device_th_pad_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&device_th_pad_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_value), MP_ROM_PTR(&device_th_pad_value_obj) },
};





MP_STATIC MP_DEFINE_CONST_DICT(device_th_pad_locals_dict, device_th_pad_locals_dict_table);


const mp_obj_type_t device_touch_pad_type = {
    { &mp_type_type },
    .name = MP_QSTR_TOUCH_PAD,
    .print = device_th_pad_print,
    .make_new = mp_th_pad_make_new,
    .locals_dict = (mp_obj_dict_t *)&device_th_pad_locals_dict,
};



#endif


