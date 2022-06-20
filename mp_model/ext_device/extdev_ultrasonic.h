#ifndef  EXTDEV_ULTRASONIC_H
#define  EXTDEV_ULTRASONIC_H



#include "hi_io.h"
#include "hi_gpio.h"



typedef struct _extdev_ultra_obj_t {
    mp_obj_base_t base;
	gpio_func  trig_pin;
	gpio_func  echo_pin;
	uint64_t   time_frist;
	uint64_t   time_last;
	int8_t     finsh_flag;
} extdev_ultra_obj_t;









#endif


