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
#include "hi_time.h"
#include "iot_gpio.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/stream.h"
#include "py/mperrno.h"
#include "mod_extdevice.h"
#include "parse_pin.h"
#include "cmsis_os2.h" 
#include "extdev_ultrasonic.h"






#if BUILD_BOARD == DASHIXIONG_BOARD
#if 1
void ultrasonic_on_falling(char *arg){
	extdev_ultra_obj_t *self = (extdev_ultra_obj_t *)arg;
	if(self != NULL){
		self->time_last = hi_get_us();
		IoTGpioUnregisterIsrFunc(self->echo_pin.gpio_id);
		self->finsh_flag = 1;
	}
	
}


void ultrasonic_on_rising(char *arg){
	extdev_ultra_obj_t *self = (extdev_ultra_obj_t *)arg;
	if(self != NULL){
		self->time_frist = hi_get_us();
		/* 注销中断 */
		IoTGpioUnregisterIsrFunc(self->echo_pin.gpio_id);
		IoTGpioRegisterIsrFunc(self->echo_pin.gpio_id,IOT_INT_TYPE_EDGE,IOT_GPIO_EDGE_FALL_LEVEL_LOW,ultrasonic_on_falling,arg);
		
	}
}
#endif

#if 0
uint32_t DFRobot_URM10::getDistanceCM(int trigPin, int echoPin)
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  long duration;
  if (digitalRead(echoPin) == 0)
  {
    digitalWrite(trigPin, LOW);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(20);
    digitalWrite(trigPin, LOW);
    duration = myPulseIn(echoPin, HIGH);
  }
  else
  {
    digitalWrite(trigPin, HIGH);
    digitalWrite(trigPin, LOW);
    duration = myPulseIn(echoPin, LOW);
  }

  duration = duration / 59;
  // if ((duration <=0) || (duration > 500)) return 0;
  delay(10);
  return duration;
}

uint64_t DFRobot_URM10::myPulseIn(uint32_t pin, uint32_t value, long maxDuration)
{
  int pulse = value == 1 ? 1 : 0;
  uint64_t tick = hi_get_us();
  uint64_t maxd = (uint64_t)maxDuration;
  IotGpioValue io_val=0;
  IoTGpioGetInputVal(pin,&io_val);
  while (io_val != pulse)
  {
  	IoTGpioGetInputVal(pin,&io_val);
    if (hi_get_us() - tick > maxd)
      return 0;
  }
  uint64_t start = hi_get_us();
  IoTGpioGetInputVal(pin,&io_val);
  while (io_val == pulse)
  {
  	IoTGpioGetInputVal(pin,&io_val);
    if (hi_get_us() - tick > maxd)
      return 0;
  }
  uint64_t end = hi_get_us();
  return end - start;
}
#endif


MP_STATIC int extdev_ultra_obj_init_helper(extdev_ultra_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
	enum { ARG_trig, ARG_echo };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_trig, MP_ARG_INT, {.u_int = -1}},
        { MP_QSTR_echo, MP_ARG_INT, {.u_int = -1}},
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);
	//printf("args[ARG_echo].u_int = %d, args[ARG_trig].u_int = %d\r\n",args[ARG_echo].u_int,args[ARG_trig].u_int);
	if(args[ARG_trig].u_int != -1){
		/* scl是关键字参数 */
		s_pin parse_pin = parse_single_pin(args[ARG_trig].u_int);
		if(parse_pin.gpio_aux.gpio_id != HI_GPIO_IDX_MAX){
			self->trig_pin = parse_pin.gpio_aux;
		}
	}else{
		if(self->trig_pin.gpio_id = HI_GPIO_IDX_MAX){
			s_pin parse_pin = parse_single_pin(15);
			if(parse_pin.gpio_aux.gpio_id != HI_GPIO_IDX_MAX){
				self->trig_pin = parse_pin.gpio_aux;
			}
		}
	}
	if(args[ARG_echo].u_int != -1){
		s_pin parse_pin = parse_single_pin(args[ARG_echo].u_int);
		if(parse_pin.gpio_aux.gpio_id != HI_GPIO_IDX_MAX){
			self->echo_pin = parse_pin.gpio_aux;
		}
	}else{
		if(self->echo_pin.gpio_id = HI_GPIO_IDX_MAX){
			s_pin parse_pin = parse_single_pin(16);
			if(parse_pin.gpio_aux.gpio_id != HI_GPIO_IDX_MAX){
				self->echo_pin = parse_pin.gpio_aux;
			}
		}
	}
	/* 初始化gpio口 */
	IoTGpioDeinit(self->trig_pin.gpio_id);
	IoTGpioInit(self->trig_pin.gpio_id);
	IoTGpioDeinit(self->echo_pin.gpio_id);
	IoTGpioInit(self->echo_pin.gpio_id);
	hi_io_set_func(self->trig_pin.gpio_id,self->trig_pin.func);
	hi_io_set_func(self->echo_pin.gpio_id,self->echo_pin.func);
	
	
	
	IoTGpioSetDir(self->trig_pin.gpio_id,HI_GPIO_DIR_OUT);
	IoTGpioSetDir(self->echo_pin.gpio_id,HI_GPIO_DIR_IN);
	IoTGpioSetOutputVal(self->trig_pin.gpio_id,0);
	/* 注册中断 */
	IoTGpioUnregisterIsrFunc(self->echo_pin.gpio_id);
	//IoTGpioRegisterIsrFunc(self->echo_pin.gpio_id,IOT_INT_TYPE_EDGE,IOT_GPIO_EDGE_RISE_LEVEL_HIGH,ultrasonic_on_rising,self);
	return 0;
}


MP_STATIC mp_obj_t extdev_ultra_obj_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
	extdev_ultra_obj_t *self = args[0];
	extdev_ultra_obj_init_helper(self, n_args - 1, args + 1, kw_args);
	return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(extdev_ultra_obj_init_obj, 3, extdev_ultra_obj_init);

MP_STATIC mp_obj_t extdev_ultra_get_distance(size_t n_args, const mp_obj_t *args) {
	extdev_ultra_obj_t *self = args[0];
	uint64_t time_out = hi_get_us();
	IoTGpioUnregisterIsrFunc(self->echo_pin.gpio_id);
	IoTGpioRegisterIsrFunc(self->echo_pin.gpio_id,IOT_INT_TYPE_EDGE,IOT_GPIO_EDGE_RISE_LEVEL_HIGH,ultrasonic_on_rising,self);
	IoTGpioSetOutputVal(self->trig_pin.gpio_id,1);
	hi_udelay(30);
	IoTGpioSetOutputVal(self->trig_pin.gpio_id,0);
	self->finsh_flag = 0;
	
	while(self->finsh_flag==0){
		if(hi_get_us() - time_out>1500000){
			//self->finsh_flag = 2;
			break;
		}
	}
	IoTGpioUnregisterIsrFunc(self->echo_pin.gpio_id);
	if(self->finsh_flag==0){
		return MP_OBJ_NEW_SMALL_INT(-1);
	}
	/* 计算距离 */
	//printf("last_time = %d\r\n,frist_time = %d\r\n",self->time_last,self->time_frist);
	uint64_t diff_time =  self->time_last-self->time_frist;
	return MP_OBJ_NEW_SMALL_INT(diff_time*340/2/1000);
	
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(extdev_ultra_get_distance_obj, 1, 1, extdev_ultra_get_distance);

MP_STATIC void extdev_ultra_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    extdev_ultra_obj_t *self = self_in;
    mp_printf(print, "ultra device driver");
}

mp_obj_t extdev_ultra_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 2, 2, true);
	extdev_ultra_obj_t *self = m_new_obj(extdev_ultra_obj_t);
	memset(self,0,sizeof(extdev_ultra_obj_t));
	self->base.type = type;
	self->trig_pin.gpio_id = HI_GPIO_IDX_MAX;
	self->echo_pin.gpio_id = HI_GPIO_IDX_MAX;
    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    int ret = extdev_ultra_obj_init_helper(self, n_args , args , &kw_args);
	if(ret==0){
    	return MP_OBJ_FROM_PTR(self);
	}else{
		return mp_const_none;
	}
}




MP_STATIC const mp_rom_map_elem_t extdev_ultra_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&extdev_ultra_obj_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_distance), MP_ROM_PTR(&extdev_ultra_get_distance_obj) },
};

MP_STATIC MP_DEFINE_CONST_DICT(extdev_ultra_locals_dict, extdev_ultra_locals_dict_table);



const mp_obj_type_t extdev_ultra_type = {
    { &mp_type_type },
    .name = MP_QSTR_Ultrasonic,
    .print = extdev_ultra_print,
    .make_new = extdev_ultra_make_new,
    .locals_dict = (mp_obj_dict_t *)&extdev_ultra_locals_dict,
};
#endif




