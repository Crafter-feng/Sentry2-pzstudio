#ifndef  EXTDEV_DHTXX_H
#define  EXTDEV_DHTXX_H



#include "hi_io.h"
#include "hi_gpio.h"



typedef struct _extdev_dhtxx_obj_t {
    mp_obj_base_t base;
	gpio_func     wire_pin;
	unsigned long long  delay_time;
} extdev_dhtxx_obj_t;









#endif


