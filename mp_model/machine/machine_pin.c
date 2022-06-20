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


#define GPIO_PULL_DOWN (1)
#define GPIO_PULL_UP   (2)

#define GPIO_MODE_INPUT  HI_GPIO_DIR_IN
#define GPIO_MODE_OUTPUT HI_GPIO_DIR_OUT




typedef struct _machine_pin_obj_t {
    mp_obj_base_t base;
    hi_gpio_idx    id;
	hi_u8          func;
	hi_gpio_dir    dir;
} machine_pin_obj_t;



MP_STATIC mp_obj_t machine_pin_obj_init_helper(machine_pin_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_mode, ARG_pull };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_mode, MP_ARG_OBJ, {.u_obj = mp_const_none}},
        { MP_QSTR_pull, MP_ARG_OBJ, {.u_obj = MP_OBJ_NEW_SMALL_INT(-1)}},
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);
	hi_io_set_func(self->id,self->func);
	self->dir = HI_GPIO_DIR_IN;	
	hi_gpio_set_dir(self->id,HI_GPIO_DIR_IN);
    // configure mode
    if (args[ARG_mode].u_obj != mp_const_none) {
        mp_int_t pin_io_mode = mp_obj_get_int(args[ARG_mode].u_obj);
		if(pin_io_mode == HI_GPIO_DIR_IN){
			self->dir = HI_GPIO_DIR_IN;
			hi_gpio_set_dir(self->id,HI_GPIO_DIR_IN);
		}else{
			self->dir = HI_GPIO_DIR_OUT;
			hi_gpio_set_dir(self->id,HI_GPIO_DIR_OUT);
		}
        
    }
    if (args[ARG_pull].u_obj != MP_OBJ_NEW_SMALL_INT(-1)) {
        int mode = 0;
        if (args[ARG_pull].u_obj != mp_const_none) {
            mode = mp_obj_get_int(args[ARG_pull].u_obj);
        }
        if(mode == GPIO_PULL_DOWN){
        	hi_io_set_pull(self->id,HI_IO_PULL_DOWN);
        }else{
            hi_io_set_pull(self->id,HI_IO_PULL_UP);
        }
    }
	IoTGpioInit(self->id);
    return mp_const_none;
}




MP_STATIC mp_obj_t machine_pin_call(mp_obj_t self_in, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 0, 1, false);
    machine_pin_obj_t *self = self_in;
	IotGpioValue val;
    if (n_args == 0) {
        if(self->dir == HI_GPIO_DIR_IN){
			IoTGpioGetInputVal(self->id,&val);
        	return MP_OBJ_NEW_SMALL_INT(val);
        }else{
			IoTGpioGetOutputVal(self->id,&val);
        	return MP_OBJ_NEW_SMALL_INT(val);
		}
    } else {
        IoTGpioSetOutputVal(self->id, mp_obj_is_true(args[0]));
        return mp_const_none;
    }
}












// pin.init(mode, pull)
MP_STATIC mp_obj_t machine_pin_obj_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    return machine_pin_obj_init_helper(args[0], n_args - 1, args + 1, kw_args);
}
MP_DEFINE_CONST_FUN_OBJ_KW(machine_pin_init_obj, 1, machine_pin_obj_init);



// pin.value([value])
MP_STATIC mp_obj_t machine_pin_value(size_t n_args, const mp_obj_t *args) {
    return machine_pin_call(args[0], n_args - 1, 0, args + 1);
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(machine_pin_value_obj, 1, 2, machine_pin_value);



// pin.off()
MP_STATIC mp_obj_t machine_pin_off(mp_obj_t self_in) {
    machine_pin_obj_t *self = MP_OBJ_TO_PTR(self_in);
    IoTGpioSetOutputVal(self->id, 0);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(machine_pin_off_obj, machine_pin_off);



// pin.on()
MP_STATIC mp_obj_t machine_pin_on(mp_obj_t self_in) {
    machine_pin_obj_t *self = MP_OBJ_TO_PTR(self_in);
    IoTGpioSetOutputVal(self->id, 1);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(machine_pin_on_obj, machine_pin_on);



MP_STATIC mp_obj_t machine_pin_set_mode(mp_obj_t self_in, mp_obj_t _mode) {
    machine_pin_obj_t *self = MP_OBJ_TO_PTR(self_in);
     mp_int_t pin_io_mode = mp_obj_get_int(_mode);
	if(pin_io_mode == HI_GPIO_DIR_IN){
		self->dir = HI_GPIO_DIR_IN;
		hi_gpio_set_dir(self->id,HI_GPIO_DIR_IN);
	}else{
		self->dir = HI_GPIO_DIR_OUT;
		hi_gpio_set_dir(self->id,HI_GPIO_DIR_OUT);
	}
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_2(machine_pin_set_mode_obj, machine_pin_set_mode);




MP_STATIC void machine_pin_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    machine_pin_obj_t *self = self_in;
    mp_printf(print, "Pin(%u)", self->id);
}









mp_obj_t mp_pin_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 1, MP_OBJ_FUN_ARGS_MAX, true);
	
    // get the wanted pin object
    int wanted_pin = mp_obj_get_int(args[0]);
    machine_pin_obj_t *self = m_new_obj(machine_pin_obj_t);
	memset(self,0,sizeof(machine_pin_obj_t));
	s_pin parse_pin = parse_single_pin(wanted_pin);
	
    if (parse_pin.gpio_aux.gpio_id != HI_GPIO_IDX_MAX) {
        self->base.type = &machine_pin_type;
		self->id = parse_pin.gpio_aux.gpio_id;
		self->func = parse_pin.gpio_aux.func;
    }
    if (self->base.type == NULL) {
        mp_raise_ValueError(MP_ERROR_TEXT("invalid pin"));
    }
	
    if (n_args > 1 || n_kw > 0) {
        // pin mode given, so configure this GPIO
        mp_map_t kw_args;
        mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
        machine_pin_obj_init_helper(self, n_args - 1, args + 1, &kw_args);
    }
    return MP_OBJ_FROM_PTR(self);
}





MP_STATIC const mp_rom_map_elem_t machine_pin_locals_dict_table[] = {
    // instance methods
    { MP_ROM_QSTR(MP_QSTR_init),  MP_ROM_PTR(&machine_pin_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_value), MP_ROM_PTR(&machine_pin_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_off),   MP_ROM_PTR(&machine_pin_off_obj) },
    { MP_ROM_QSTR(MP_QSTR_on),    MP_ROM_PTR(&machine_pin_on_obj) },
    { MP_ROM_QSTR(MP_QSTR_mode),  MP_ROM_PTR(&machine_pin_set_mode_obj) },
    // class constants
    { MP_ROM_QSTR(MP_QSTR_IN), MP_ROM_INT(HI_GPIO_DIR_IN) },
    { MP_ROM_QSTR(MP_QSTR_OUT), MP_ROM_INT(HI_GPIO_DIR_OUT) },
    { MP_ROM_QSTR(MP_QSTR_PULL_UP), MP_ROM_INT(GPIO_PULL_UP) },
    { MP_ROM_QSTR(MP_QSTR_PULL_DOWN), MP_ROM_INT(GPIO_PULL_DOWN) },
};



MP_STATIC MP_DEFINE_CONST_DICT(machine_pin_locals_dict, machine_pin_locals_dict_table);

const mp_obj_type_t machine_pin_type = {
    { &mp_type_type },
    .name = MP_QSTR_Pin,
    .print = machine_pin_print,
    .make_new = mp_pin_make_new,
    .locals_dict = (mp_obj_dict_t *)&machine_pin_locals_dict,
};







