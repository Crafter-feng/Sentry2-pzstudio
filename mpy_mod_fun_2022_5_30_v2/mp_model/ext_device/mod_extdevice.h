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
