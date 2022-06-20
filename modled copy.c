#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "py/obj.h"
#include "py/runtime.h"
#include "iot_gpio.h" 

mp_obj_t mp_led_init(mp_obj_t index) {
    int i = mp_obj_get_int(index);
    IoTGpioInit(i);
    IoTGpioSetDir(i, IOT_GPIO_DIR_OUT);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_led_init_obj, mp_led_init);

mp_obj_t mp_led_on(mp_obj_t index) {
    int i = mp_obj_get_int(index);
    IoTGpioSetOutputVal(i, 1);      
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_led_on_obj, mp_led_on);

mp_obj_t mp_led_off(mp_obj_t index) {
    int i = mp_obj_get_int(index);
    IoTGpioSetOutputVal(i, 0);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_led_off_obj, mp_led_off);

MP_STATIC const mp_rom_map_elem_t led_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_led) },
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mp_led_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_on), MP_ROM_PTR(&mp_led_on_obj) },
    { MP_ROM_QSTR(MP_QSTR_off), MP_ROM_PTR(&mp_led_off_obj) },
};

MP_STATIC MP_DEFINE_CONST_DICT(led_module_globals, led_module_globals_table);

const mp_obj_module_t mp_module_led = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&led_module_globals,
};
