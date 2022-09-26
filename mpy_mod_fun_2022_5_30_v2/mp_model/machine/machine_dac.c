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


#include <stdio.h>

#include "py/runtime.h"
#include "py/mphal.h"
#include "modmachine.h"

#if MICROPY_PY_MACHINE_DAC

#include "driver/gpio.h"
#include "driver/dac.h"

typedef struct _mdac_obj_t {
    mp_obj_base_t base;
    gpio_num_t gpio_id;
    dac_channel_t dac_id;
} mdac_obj_t;

MP_STATIC const mdac_obj_t mdac_obj[] = {
    #if CONFIG_IDF_TARGET_ESP32
    {{&machine_dac_type}, GPIO_NUM_25, DAC_CHANNEL_1},
    {{&machine_dac_type}, GPIO_NUM_26, DAC_CHANNEL_2},
    #else
    {{&machine_dac_type}, GPIO_NUM_17, DAC_CHANNEL_1},
    {{&machine_dac_type}, GPIO_NUM_18, DAC_CHANNEL_2},
    #endif
};

MP_STATIC mp_obj_t mdac_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw,
    const mp_obj_t *args) {

    mp_arg_check_num(n_args, n_kw, 1, 1, true);
    gpio_num_t pin_id = machine_pin_get_id(args[0]);
    const mdac_obj_t *self = NULL;
    for (int i = 0; i < MP_ARRAY_SIZE(mdac_obj); i++) {
        if (pin_id == mdac_obj[i].gpio_id) {
            self = &mdac_obj[i];
            break;
        }
    }
    if (!self) {
        mp_raise_ValueError(MP_ERROR_TEXT("invalid Pin for DAC"));
    }

    esp_err_t err = dac_output_enable(self->dac_id);
    if (err == ESP_OK) {
        err = dac_output_voltage(self->dac_id, 0);
    }
    if (err == ESP_OK) {
        return MP_OBJ_FROM_PTR(self);
    }
    mp_raise_ValueError(MP_ERROR_TEXT("parameter error"));
}

MP_STATIC void mdac_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    mdac_obj_t *self = self_in;
    mp_printf(print, "DAC(Pin(%u))", self->gpio_id);
}

MP_STATIC mp_obj_t mdac_write(mp_obj_t self_in, mp_obj_t value_in) {
    mdac_obj_t *self = self_in;
    int value = mp_obj_get_int(value_in);
    if (value < 0 || value > 255) {
        mp_raise_ValueError(MP_ERROR_TEXT("value out of range"));
    }

    esp_err_t err = dac_output_voltage(self->dac_id, value);
    if (err == ESP_OK) {
        return mp_const_none;
    }
    mp_raise_ValueError(MP_ERROR_TEXT("parameter error"));
}
MP_DEFINE_CONST_FUN_OBJ_2(mdac_write_obj, mdac_write);

MP_STATIC const mp_rom_map_elem_t mdac_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_write), MP_ROM_PTR(&mdac_write_obj) },
};

MP_STATIC MP_DEFINE_CONST_DICT(mdac_locals_dict, mdac_locals_dict_table);

const mp_obj_type_t machine_dac_type = {
    { &mp_type_type },
    .name = MP_QSTR_DAC,
    .print = mdac_print,
    .make_new = mdac_make_new,
    .locals_dict = (mp_obj_t)&mdac_locals_dict,
};

#endif // MICROPY_PY_MACHINE_DAC
