#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "unistd.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "iot_gpio.h" 
#include <unistd.h>

mp_obj_t mp_time_sleep(mp_obj_t seconds_o) {


	#if MICROPY_PY_BUILTINS_FLOAT
	if(mp_obj_is_int(seconds_o)){
		int i = mp_obj_get_int(seconds_o);
		sleep(i);
	}
	else if(mp_obj_is_float(seconds_o)){
		usleep((mp_uint_t)(1000000 * mp_obj_get_float(seconds_o)));
	}
    #else
	int i = mp_obj_get_int(seconds_o);
	sleep(i);
    #endif
    
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_sleep_obj, mp_time_sleep);


mp_obj_t mp_time_usleep(mp_obj_t index) {
    int i = mp_obj_get_int(index);
    usleep(i);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_usleep_obj, mp_time_usleep);


mp_obj_t mp_time_msleep(mp_obj_t index) {
    int i = mp_obj_get_int(index);
    usleep(i*1000);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_msleep_obj, mp_time_msleep);



mp_obj_t mp_tick_ms(mp_obj_t index) {
    UINT64 tickCount = LOS_TickCountGet();
    return mp_obj_new_int(LOS_Tick2MS(tickCount));
}

MP_DEFINE_CONST_FUN_OBJ_0(mp_tick_ms_obj, mp_tick_ms);
MP_STATIC const mp_rom_map_elem_t time_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_time) },
    { MP_ROM_QSTR(MP_QSTR_sleep), MP_ROM_PTR(&mp_sleep_obj) },
    { MP_ROM_QSTR(MP_QSTR_msleep), MP_ROM_PTR(&mp_msleep_obj) },
    { MP_ROM_QSTR(MP_QSTR_usleep), MP_ROM_PTR(&mp_usleep_obj) },
    { MP_ROM_QSTR(MP_QSTR_tick_ms), MP_ROM_PTR(&mp_tick_ms_obj) },
};

MP_STATIC MP_DEFINE_CONST_DICT(time_module_globals, time_module_globals_table);

const mp_obj_module_t mp_module_time = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&time_module_globals,
};
