#ifndef MICROPY_INCLUDED_HI3861_MODDEVICE_H
#define MICROPY_INCLUDED_HI3861_MODDEVICE_H

#include "py/obj.h"
#include "modmachine.h"

#if BUILD_BOARD == DASHIXIONG_BOARD
extern const mp_obj_type_t device_us516p6_type;
extern const mp_obj_type_t device_oled_type;
extern const mp_obj_type_t device_imu_type;
extern const mp_obj_type_t device_motor_type;
extern const mp_obj_type_t device_beep_type;
extern const mp_obj_type_t device_led_type;
extern const mp_obj_type_t device_button_type;
extern const mp_obj_type_t device_servo_type;
extern const mp_obj_type_t device_thumi_temp_type;
extern const mp_obj_type_t device_mic_type;
extern const mp_obj_type_t device_light_sen_type;


#elif BUILD_BOARD == TQ_BOARD
extern const mp_obj_type_t device_beep_type;
extern const mp_obj_type_t device_led_type;
extern const mp_obj_type_t device_matrix_type;
extern const mp_obj_type_t device_imu_type;
extern const mp_obj_type_t device_button_type;
extern const mp_obj_type_t device_thumi_temp_type;
extern const mp_obj_type_t device_touch_pad_type;
extern const mp_obj_type_t device_mic_type;
extern const mp_obj_type_t device_light_sen_type;
#endif

#endif // MICROPY_INCLUDED_ESP32_MODMACHINE_H
