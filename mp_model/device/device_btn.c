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


typedef struct _device_btn_obj_t {
    mp_obj_base_t base;
	uint8_t id;
	uint8_t pin;
} device_btn_obj_t;



MP_STATIC mp_obj_t device_btn_obj_init_helper(device_btn_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    IoTGpioInit(self->pin);
	if(self->pin == HI_GPIO_IDX_2){
		hi_io_set_func(self->pin, HI_IO_FUNC_GPIO_2_GPIO);
	}else if(self->pin == HI_GPIO_IDX_10){
		hi_io_set_func(self->pin, HI_IO_FUNC_GPIO_10_GPIO);
	}
	IoTGpioSetDir(self->pin,IOT_GPIO_DIR_IN);
	hi_io_set_pull(self->pin,HI_IO_PULL_UP);
    return mp_const_none;
}




// pin.init(mode, pull)
MP_STATIC mp_obj_t device_btn_obj_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
	return device_btn_obj_init_helper(args[0], n_args - 1, args + 1, kw_args);
}
MP_DEFINE_CONST_FUN_OBJ_KW(device_btn_init_obj, 1, device_btn_obj_init);





//(mp_obj_t self_in, size_t n_args, size_t n_kw, const mp_obj_t *args)
MP_STATIC mp_obj_t device_btn_value(size_t n_args, const mp_obj_t *args) {
    device_btn_obj_t *self = args[0];
	IotGpioValue val;
	IoTGpioGetInputVal(self->pin,&val);
	return MP_OBJ_NEW_SMALL_INT(val);
    
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(device_btn_value_obj, 1, 1, device_btn_value);





MP_STATIC void device_btn_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    device_btn_obj_t *self = self_in;
    mp_printf(print, "BUTTON(%u)", self->id);
}



mp_obj_t mp_btn_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 1, 1, true);
    int led_num = mp_obj_get_int(args[0]);
    device_btn_obj_t *self = m_new_obj(device_btn_obj_t);
	memset(self,0,sizeof(device_btn_obj_t));
	self->base.type = &device_button_type;
	self->id = led_num;
	if(self->id==1){
		self->pin= HI_GPIO_IDX_2;
	}else if(self->id==0){
		self->pin= HI_GPIO_IDX_10;
	}else{
		mp_raise_ValueError(MP_ERROR_TEXT("invalid btn"));
	}
    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    device_btn_obj_init_helper(self, n_args - 1, args + 1, &kw_args);
    return MP_OBJ_FROM_PTR(self);
}





MP_STATIC const mp_rom_map_elem_t device_btn_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&device_btn_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_value), MP_ROM_PTR(&device_btn_value_obj) },
};





MP_STATIC MP_DEFINE_CONST_DICT(device_btn_locals_dict, device_btn_locals_dict_table);
const mp_obj_type_t device_button_type = {
    { &mp_type_type },
    .name = MP_QSTR_BUTTON,
    .print = device_btn_print,
    .make_new = mp_btn_make_new,
    .locals_dict = (mp_obj_dict_t *)&device_btn_locals_dict,
};



#elif BUILD_BOARD == TQ_BOARD




typedef struct _device_btn_obj_t {
    mp_obj_base_t base;
	uint8_t id;
	uint8_t pin;
} device_btn_obj_t;



MP_STATIC mp_obj_t device_btn_obj_init_helper(device_btn_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    IoTGpioInit(self->pin);
	if(self->pin == HI_GPIO_IDX_7){
		hi_io_set_func(self->pin, HI_IO_FUNC_GPIO_7_GPIO);
	}else if(self->pin == HI_GPIO_IDX_8){
		hi_io_set_func(self->pin, HI_IO_FUNC_GPIO_8_GPIO);
	}
	hi_io_set_pull(self->pin, 1);
	IoTGpioSetDir(self->pin,IOT_GPIO_DIR_IN);
    return mp_const_none;
}




// pin.init(mode, pull)
MP_STATIC mp_obj_t device_btn_obj_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
	return device_btn_obj_init_helper(args[0], n_args - 1, args + 1, kw_args);
}
MP_DEFINE_CONST_FUN_OBJ_KW(device_btn_init_obj, 1, device_btn_obj_init);





//(mp_obj_t self_in, size_t n_args, size_t n_kw, const mp_obj_t *args)
MP_STATIC mp_obj_t device_btn_value(size_t n_args, const mp_obj_t *args) {
    device_btn_obj_t *self = args[0];
	IotGpioValue val;
	IoTGpioGetInputVal(self->pin,&val);
	return MP_OBJ_NEW_SMALL_INT(val);
    
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(device_btn_value_obj, 1, 1, device_btn_value);





MP_STATIC void device_btn_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    device_btn_obj_t *self = self_in;
    mp_printf(print, "BUTTON(%u)", self->id);
}



mp_obj_t mp_btn_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 1, 1, true);
    int led_num = mp_obj_get_int(args[0]);
    device_btn_obj_t *self = m_new_obj(device_btn_obj_t);
	memset(self,0,sizeof(device_btn_obj_t));
	self->base.type = &device_button_type;
	self->id = led_num;
	if(self->id==0){
		self->pin=HI_GPIO_IDX_7;
		
	}else if(self->id==1){
		self->pin=HI_GPIO_IDX_8;
	}else{
		mp_raise_ValueError(MP_ERROR_TEXT("invalid btn"));
	}
    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    device_btn_obj_init_helper(self, n_args - 1, args + 1, &kw_args);
    return MP_OBJ_FROM_PTR(self);
}





MP_STATIC const mp_rom_map_elem_t device_btn_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&device_btn_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_value), MP_ROM_PTR(&device_btn_value_obj) },
};





MP_STATIC MP_DEFINE_CONST_DICT(device_btn_locals_dict, device_btn_locals_dict_table);
const mp_obj_type_t device_button_type = {
    { &mp_type_type },
    .name = MP_QSTR_BUTTON,
    .print = device_btn_print,
    .make_new = mp_btn_make_new,
    .locals_dict = (mp_obj_dict_t *)&device_btn_locals_dict,
};



#endif


