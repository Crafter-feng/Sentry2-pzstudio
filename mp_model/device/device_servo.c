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
#include "cmsis_os2.h" 


#if BUILD_BOARD == DASHIXIONG_BOARD


#define SERVO_CLK_40M   40000000
#define SERVO_DUTY_MIN  0
#define SERVO_DUTY_MAX  100
#define SERVO_SHORT_MAX 0xFFFF




#define MIN_ANGLE             0
#define MAX_ANGLE             180


#define MIN_PULSE_WIDTH       50      // the shortest pulse sent to a servo
#define MAX_PULSE_WIDTH       250     // the longest pulse sent to a servo



osThreadId_t servo_timer_id;

int servo_gpionum = 0;
int servo_duty = 0;





typedef struct _device_servo_obj_t {
    mp_obj_base_t base;
	int angle;
	hi_u8 last_angle;
	uint8_t id;
	s_pin  servo_pin;
} device_servo_obj_t;








MP_STATIC int device_servo_obj_init_helper(device_servo_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
	
	self->last_angle = 200;
	IoTGpioDeinit(self->servo_pin.io_name);
	IoTGpioInit(self->servo_pin.io_name);
	hi_io_set_func(self->servo_pin.io_name, self->servo_pin.gpio_aux.func);
    if(hi_gpio_set_dir(self->servo_pin.gpio_aux.gpio_id, HI_GPIO_DIR_OUT) != 0){
        printf("servo set gpio dir fail\r\n");
        return -1;
    }
    return 0;
}





MP_STATIC mp_obj_t device_servo_obj_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
	device_servo_obj_init_helper(args[0], n_args - 1, args + 1, kw_args);
	
	return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(device_servo_obj_init_obj, 1, device_servo_obj_init);



MP_STATIC mp_obj_t device_servo_angle(size_t n_args, const mp_obj_t *args) {
	mp_arg_check_num(n_args - 1, 0, 0, 1, args + 1);
    device_servo_obj_t *self = args[0];
	hi_u32 pulse_width;  // unit: us
	IotGpioValue val;
    if (n_args == 1) {
    	return MP_OBJ_NEW_SMALL_INT(self->angle);
    } else {
		
        self->angle  = mp_obj_get_int(args[1]);
		if(self->angle < 0){
			self->angle = 0;	
		}
		if(self->angle > 180){
			self->angle=180;
		}
		pulse_width = (hi_u32)((((self->angle / 180.0) * (2.5 - 0.5)) + 0.5) * 1000);
		for(hi_u8 i = 0; i < 30; i++){
	        if(hi_gpio_set_ouput_val(self->servo_pin.gpio_aux.gpio_id, HI_GPIO_VALUE1) != 0){
	            printf("servo set output high fail\r\n");
	            return mp_const_none;
	        }
	        hi_udelay(pulse_width);  // 宽度为pulse的高电平
	        if(hi_gpio_set_ouput_val(self->servo_pin.gpio_aux.gpio_id, HI_GPIO_VALUE0) != 0){
	            printf("servo set output low fail\r\n");
	            return mp_const_none;
	        }
	        hi_udelay(20000-pulse_width);  // 宽度为20ms - pulse的低电平
	    }
	    hi_sleep(40);  // make an interval to allow sys kick watchdog
	    self->last_angle = self->angle;
		return mp_const_none;
    }
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(device_servo_angle_obj, 1, 2, device_servo_angle);






MP_STATIC void device_servo_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    device_servo_obj_t *self = self_in;
    mp_printf(print, "Servo(%u)", self->id);
}





mp_obj_t mp_servo_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 1, 1, true);
    int gpio_num = mp_obj_get_int(args[0]);
	
	device_servo_obj_t *self = m_new_obj(device_servo_obj_t);
	memset(self,0,sizeof(device_servo_obj_t));
	s_pin parse_pin = parse_single_pin(gpio_num);
	if(parse_pin.gpio_aux.gpio_id == HI_GPIO_IDX_MAX){
		mp_raise_ValueError(MP_ERROR_TEXT("invalid pin"));
	}
	self->base.type = &device_servo_type;
	self->id = gpio_num;
	self->servo_pin = parse_pin;
    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    device_servo_obj_init_helper(self, n_args - 1, args + 1, &kw_args);
    return MP_OBJ_FROM_PTR(self);
}







MP_STATIC const mp_rom_map_elem_t device_servo_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&device_servo_obj_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_angle), MP_ROM_PTR(&device_servo_angle_obj) },
};





MP_STATIC MP_DEFINE_CONST_DICT(device_servo_locals_dict, device_servo_locals_dict_table);
const mp_obj_type_t device_servo_type = {
    { &mp_type_type },
    .name = MP_QSTR_Servo,
    .print = device_servo_print,
    .make_new = mp_servo_make_new,
    .locals_dict = (mp_obj_dict_t *)&device_servo_locals_dict,
};
#endif



