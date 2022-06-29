/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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
#include "hi_pwm.h"



// Forward dec'l
extern const mp_obj_type_t machine_pwm_type;

typedef struct _hi3861_pwm_obj_t {
    mp_obj_base_t base;
	hi_u8 id;
    hi_gpio_idx pin;
	hi_u8 gpio_func;
	hi_pwm_port pwm_port;
	hi_u8 pwm_func;
	hi_u16 freq;
	hi_u16 duty;
	hi_u8  active;
} hi3861_pwm_obj_t;




#define MP_PWM_CLK_40M    40000000
#define MP_PWM_DUTY_MIN   0
#define MP_PWM_DUTY_MAX   100
#define MP_PWM_SHORT_MAX  0xFFFF

#define PWFREQ (1000)



MP_STATIC int mp_pwm_set(hi3861_pwm_obj_t *self,unsigned int freq, unsigned short volume)
{
	unsigned int hiDuty;
    unsigned int hiFreq;
	if(volume==0){
		hi_pwm_stop(self->pwm_port);
		return 0;
	}
	
	if ((freq == 0)) {
        return -1;
    }
    if ((MP_PWM_CLK_40M / freq) > MP_PWM_SHORT_MAX) {
        return -1;
    }
	if(volume >= MP_PWM_DUTY_MAX){
		volume = MP_PWM_DUTY_MAX-1;
	}
	hiFreq = (unsigned short)(MP_PWM_CLK_40M / freq);
    hiDuty = (volume * hiFreq) / MP_PWM_DUTY_MAX;
	hi_pwm_start(self->pwm_port, hiDuty, hiFreq);
    return 0;
}



MP_STATIC int pwm_freq_check(int freq){
	if(freq == 0){
		return -1;
	}
	if ((MP_PWM_CLK_40M / freq) > MP_PWM_SHORT_MAX) {
		
        return -1;
    }
	return 0;
}


MP_STATIC int pwm_duty_check(int duty){
	if(duty == 0){
		//printf("1\r\n");
		return 0;
	}
	if((duty > MP_PWM_DUTY_MAX) || (duty < MP_PWM_DUTY_MIN)){
		//printf("2\r\n");
		return -1;
	}
	return 0;
}



/******************************************************************************/
MP_STATIC void hi3861_pwm_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    hi3861_pwm_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "PWM(%u", self->id);
    if (self->active) {
        mp_printf(print, ", freq=%u, duty=%u", self->freq,self->duty);
    }
    mp_printf(print, ")");
}



MP_STATIC int  hi3861_pwm_init_helper(hi3861_pwm_obj_t *self,size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_freq, ARG_duty };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_freq, MP_ARG_INT, {.u_int = PWFREQ} },
        { MP_QSTR_duty, MP_ARG_INT, {.u_int = 0} },
    };
	
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args,MP_ARRAY_SIZE(allowed_args), allowed_args, args);

	/* 初始化GPIO */
	IoTGpioInit(self->pin);
    hi_io_set_func(self->pin,self->pwm_func);
    IoTGpioSetDir(self->pin ,IOT_GPIO_DIR_OUT);
    hi_pwm_set_clock(PWM_CLK_XTAL);
	if(hi_pwm_init(self->pwm_port) == 0){
		self->active = 1;
	}
	
    // Maybe change PWM timer
    int tval = args[ARG_freq].u_int;
	if(pwm_freq_check(tval)!=0){
    	mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("bad frequency %d"), tval);
	}
    // Set duty cycle?
    int dval = args[ARG_duty].u_int;
	if(pwm_duty_check(dval)!=0){
    	mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("bad duty %d"), dval);
	}
	if(mp_pwm_set(self,tval,dval)==0){
		self->freq = tval;
	    self->duty = dval;
		return 0;
	}else{
		return -1;
	}    
}

MP_STATIC mp_obj_t hi3861_pwm_make_new(const mp_obj_type_t *type,
    size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 1, MP_OBJ_FUN_ARGS_MAX, true);
    //gpio_num_t pin_id = machine_pin_get_id(args[0]);
	/* 设置获取对应的通道pwm */
    // create PWM object from the given pin
	int wanted_pin = mp_obj_get_int(args[0]);

	
	s_pin parse_pin = parse_single_pin(wanted_pin);
    if (parse_pin.gpio_aux.gpio_id == HI_GPIO_IDX_MAX) {
        mp_raise_ValueError(MP_ERROR_TEXT("invalid pin"));
    }
	
	if(parse_pin.pwm_aux.pwm_ch == HI_PWM_PORT_MAX){
		mp_raise_ValueError(MP_ERROR_TEXT("invalid Pin for PWM"));
	}
    hi3861_pwm_obj_t *self = m_new_obj(hi3861_pwm_obj_t);
	self->id = wanted_pin;
    self->base.type = &machine_pwm_type;
    self->pin = parse_pin.gpio_aux.gpio_id;
	self->gpio_func = parse_pin.gpio_aux.func;
	self->pwm_port  = parse_pin.pwm_aux.pwm_ch;
	self->pwm_func  = parse_pin.pwm_aux.func;
	self->freq      = PWFREQ;
	self->duty      = 0;
    self->active = 0;
    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    int ret = hi3861_pwm_init_helper(self, n_args - 1, args + 1, &kw_args);
	if(ret==0){
    	return MP_OBJ_FROM_PTR(self);
	}else{
		return mp_const_none;
	}
}




MP_STATIC mp_obj_t hi3861_pwm_init(size_t n_args,
    const mp_obj_t *args, mp_map_t *kw_args) {
    hi3861_pwm_init_helper(args[0], n_args - 1, args + 1, kw_args);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(hi3861_pwm_init_obj, 1, hi3861_pwm_init);




MP_STATIC mp_obj_t hi3861_pwm_deinit(mp_obj_t self_in) {
    hi3861_pwm_obj_t *self = MP_OBJ_TO_PTR(self_in);
	
  	if(self->active){
		hi_pwm_deinit(self->pwm_port);
	    hi_io_set_func(self->pin,self->gpio_func);
		IoTGpioDeinit(self->pin);
		self->active = 0;
	}
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(hi3861_pwm_deinit_obj, hi3861_pwm_deinit);



MP_STATIC mp_obj_t hi3861_pwm_freq(size_t n_args, const mp_obj_t *args) {
	hi3861_pwm_obj_t *self = MP_OBJ_TO_PTR(args[0]);
	if (n_args == 1) {
        // get
        //获取 pwm 频率
        return MP_OBJ_NEW_SMALL_INT(self->freq);
    }

    // set
    // 设置 pwm 频率
    int tval = mp_obj_get_int(args[1]);
    if (pwm_freq_check(tval)) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("bad frequency %d"), tval);
    }
	if(mp_pwm_set(self,tval,self->duty)==0){
		self->freq = tval;
		return mp_const_true;
	}else{
		return mp_const_false;
	}
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(hi3861_pwm_freq_obj, 1, 2, hi3861_pwm_freq);



MP_STATIC mp_obj_t hi3861_pwm_duty(size_t n_args, const mp_obj_t *args) {
    hi3861_pwm_obj_t *self = MP_OBJ_TO_PTR(args[0]);
    if (n_args == 1) {
        // get
        // duty 获取pwm 占空比 
        return MP_OBJ_NEW_SMALL_INT(self->duty);
    }
    // set
    int duty = mp_obj_get_int(args[1]);
	if (pwm_duty_check(duty)) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("bad duty %d"), duty);
    }
    //设置pwm占空比
    if(mp_pwm_set(self,self->freq,duty)==0){
		self->duty = duty;
		return mp_const_true;
	}else{
		return mp_const_false;
	}
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(hi3861_pwm_duty_obj,1, 2, hi3861_pwm_duty);



MP_STATIC const mp_rom_map_elem_t hi3861_pwm_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&hi3861_pwm_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&hi3861_pwm_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR_freq), MP_ROM_PTR(&hi3861_pwm_freq_obj) },
    { MP_ROM_QSTR(MP_QSTR_duty), MP_ROM_PTR(&hi3861_pwm_duty_obj) },
};




MP_STATIC MP_DEFINE_CONST_DICT(hi3861_pwm_locals_dict, hi3861_pwm_locals_dict_table);


const mp_obj_type_t machine_pwm_type = {
    { &mp_type_type },
    .name = MP_QSTR_PWM,
    .print = hi3861_pwm_print,
    .make_new = hi3861_pwm_make_new,
    .locals_dict = (mp_obj_dict_t *)&hi3861_pwm_locals_dict,
};





