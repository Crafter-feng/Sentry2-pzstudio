/*
 * Copyright (C) 2022 Polygon Zone Open Source Organization .
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http:// www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 *
 * limitations under the License.
 */



#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "py/obj.h"
#include "py/runtime.h"
#include "moddevice.h"




#if BUILD_BOARD == DASHIXIONG_BOARD


MP_STATIC const mp_rom_map_elem_t device_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_device)},
    { MP_ROM_QSTR(MP_QSTR_US516P6),  MP_ROM_PTR(&device_us516p6_type)},
    { MP_ROM_QSTR(MP_QSTR_OLED),     MP_ROM_PTR(&device_oled_type)},
    { MP_ROM_QSTR(MP_QSTR_IMU),      MP_ROM_PTR(&device_imu_type)},
    { MP_ROM_QSTR(MP_QSTR_DF_MOTOR), MP_ROM_PTR(&device_motor_type)},
    { MP_ROM_QSTR(MP_QSTR_BEEP),     MP_ROM_PTR(&device_beep_type)},
    { MP_ROM_QSTR(MP_QSTR_LED),      MP_ROM_PTR(&device_led_type)},
    { MP_ROM_QSTR(MP_QSTR_BUTTON),   MP_ROM_PTR(&device_button_type)},
    { MP_ROM_QSTR(MP_QSTR_AHT2X),   MP_ROM_PTR(&device_thumi_temp_type)},
    { MP_ROM_QSTR(MP_QSTR_MIC),   MP_ROM_PTR(&device_mic_type)},
    { MP_ROM_QSTR(MP_QSTR_LIGHT_SENSOR),   MP_ROM_PTR(&device_light_sen_type)},
};

#elif BUILD_BOARD == TQ_BOARD


MP_STATIC const mp_rom_map_elem_t device_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_device)},
    { MP_ROM_QSTR(MP_QSTR_BEEP),     MP_ROM_PTR(&device_beep_type)},
    { MP_ROM_QSTR(MP_QSTR_LED),      MP_ROM_PTR(&device_led_type)},
    { MP_ROM_QSTR(MP_QSTR_MATRIX_SCREEN),      MP_ROM_PTR(&device_matrix_type)},
    { MP_ROM_QSTR(MP_QSTR_IMU),      MP_ROM_PTR(&device_imu_type)},
    { MP_ROM_QSTR(MP_QSTR_BUTTON),   MP_ROM_PTR(&device_button_type)},
    { MP_ROM_QSTR(MP_QSTR_AHT2X),   MP_ROM_PTR(&device_thumi_temp_type)},
    { MP_ROM_QSTR(MP_QSTR_TOUCH_PAD),   MP_ROM_PTR(&device_touch_pad_type)},
    { MP_ROM_QSTR(MP_QSTR_MIC),   MP_ROM_PTR(&device_mic_type)},
    { MP_ROM_QSTR(MP_QSTR_LIGHT_SENSOR),   MP_ROM_PTR(&device_light_sen_type)},
};
#endif




MP_STATIC MP_DEFINE_CONST_DICT(device_module_globals, device_module_globals_table);

const mp_obj_module_t mp_module_device = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&device_module_globals,
};



