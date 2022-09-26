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
 
 
 
 

#include <string.h>

#include "py/nlr.h"
#include "py/obj.h"
#include "py/runtime.h"

#include "esp_task_wdt.h"

const mp_obj_type_t machine_wdt_type;

typedef struct _machine_wdt_obj_t {
    mp_obj_base_t base;
} machine_wdt_obj_t;

MP_STATIC machine_wdt_obj_t wdt_default = {{&machine_wdt_type}};

MP_STATIC mp_obj_t machine_wdt_make_new(const mp_obj_type_t *type_in, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    enum { ARG_id, ARG_timeout };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_id, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_timeout, MP_ARG_INT, {.u_int = 5000} }
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, all_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    if (args[ARG_id].u_int != 0) {
        mp_raise_ValueError(NULL);
    }

    // Convert milliseconds to seconds (esp_task_wdt_init needs seconds)
    args[ARG_timeout].u_int /= 1000;

    if (args[ARG_timeout].u_int <= 0) {
        mp_raise_ValueError(MP_ERROR_TEXT("WDT timeout too short"));
    }

    mp_int_t rs_code = esp_task_wdt_init(args[ARG_timeout].u_int, true);
    if (rs_code != ESP_OK) {
        mp_raise_OSError(rs_code);
    }

    esp_task_wdt_add(NULL);

    return &wdt_default;
}

MP_STATIC mp_obj_t machine_wdt_feed(mp_obj_t self_in) {
    (void)self_in;
    esp_task_wdt_reset();
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(machine_wdt_feed_obj, machine_wdt_feed);

MP_STATIC const mp_rom_map_elem_t machine_wdt_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_feed), MP_ROM_PTR(&machine_wdt_feed_obj) },
};
MP_STATIC MP_DEFINE_CONST_DICT(machine_wdt_locals_dict, machine_wdt_locals_dict_table);

const mp_obj_type_t machine_wdt_type = {
    { &mp_type_type },
    .name = MP_QSTR_WDT,
    .make_new = machine_wdt_make_new,
    .locals_dict = (mp_obj_t)&machine_wdt_locals_dict,
};
