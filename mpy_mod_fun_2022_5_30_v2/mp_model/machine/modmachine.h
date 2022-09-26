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




#ifndef MICROPY_INCLUDED_HI3861_MODMACHINE_H
#define MICROPY_INCLUDED_HI3861_MODMACHINE_H

#include "py/obj.h"

extern const mp_obj_type_t machine_uart_type;
extern const mp_obj_type_t mp_machine_i2c_type;
extern const mp_obj_type_t machine_pin_type;
extern const mp_obj_type_t machine_pwm_type;
extern const mp_obj_type_t machine_adc_type;

#endif // MICROPY_INCLUDED_ESP32_MODMACHINE_H
