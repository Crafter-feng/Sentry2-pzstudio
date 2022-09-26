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
#include "mod_extdevice.h"




#if BUILD_BOARD == DASHIXIONG_BOARD 
MP_STATIC const mp_rom_map_elem_t ext_device_module_globals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_ext_device)},
    {MP_ROM_QSTR(MP_QSTR_Ttp229),   MP_ROM_PTR(&extdev_ttp229_type)},
	{MP_ROM_QSTR(MP_QSTR_Ultrasonic),  MP_ROM_PTR(&extdev_ultra_type)},
	{MP_ROM_QSTR(MP_QSTR_Dhtxx),   MP_ROM_PTR(&extdev_DHTxx_type)},
	{MP_ROM_QSTR(MP_QSTR_Servo),    MP_ROM_PTR(&device_servo_type)},
	{MP_ROM_QSTR(MP_QSTR_PMxx),    MP_ROM_PTR(&extdev_pmxx_type)},
};

#elif BUILD_BOARD == TQ_BOARD
MP_STATIC const mp_rom_map_elem_t ext_device_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_ext_device)},
    
};
#endif




MP_STATIC MP_DEFINE_CONST_DICT(ext_device_module_globals, ext_device_module_globals_table);
const mp_obj_module_t mp_module_ext_device = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&ext_device_module_globals,
};



