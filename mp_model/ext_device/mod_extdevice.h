#ifndef MICROPY_INCLUDED_HI3861_MOD_EXTDEVICE_H
#define MICROPY_INCLUDED_HI3861_MOD_EXTDEVICE_H

#include "py/obj.h"
#include "modmachine.h"

#if BUILD_BOARD == DASHIXIONG_BOARD
extern const mp_obj_type_t extdev_ttp229_type;
extern const mp_obj_type_t extdev_ultra_type;
extern const mp_obj_type_t extdev_DHTxx_type;
extern const mp_obj_type_t device_servo_type;
extern const mp_obj_type_t extdev_pmxx_type;


#elif BUILD_BOARD == TQ_BOARD



#endif

#endif // MICROPY_INCLUDED_ESP32_MODMACHINE_H
