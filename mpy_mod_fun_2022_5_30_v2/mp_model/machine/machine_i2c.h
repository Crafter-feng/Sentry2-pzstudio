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
 
 
 
#ifndef MICROPY_INCLUDED_MACHINE_I2C_H
#define MICROPY_INCLUDED_MACHINE_I2C_H

#include "py/obj.h"
#include "py/mphal.h"


#define MP_MACHINE_I2C_FLAG_READ (0x01) // if not set then it's a write
#define MP_MACHINE_I2C_FLAG_STOP (0x02)

typedef struct _mp_machine_i2c_buf_t {
    size_t len;
    uint8_t *buf;
} mp_machine_i2c_buf_t;

// I2C protocol
// - init must be non-NULL
// - start/stop/read/write can be NULL, meaning operation is not supported
// - transfer must be non-NULL
// - transfer_single only needs to be set if transfer=mp_machine_i2c_transfer_adaptor
typedef struct _mp_machine_i2c_p_t {
    void (*init)(mp_obj_base_t *obj, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args);
    int (*transfer)(mp_obj_base_t *obj, uint16_t addr, size_t n, mp_machine_i2c_buf_t *bufs, unsigned int flags);
    int (*transfer_single)(mp_obj_base_t *obj, uint16_t addr, size_t len, uint8_t *buf, unsigned int flags);
} mp_machine_i2c_p_t;

typedef struct _mp_machine_soft_i2c_obj_t {
    mp_obj_base_t base;
	int id;
	uint32_t freq;
} mp_machine_i2c_obj_t;



int mp_machine_soft_i2c_transfer(mp_obj_base_t *self, uint16_t addr, size_t n, mp_machine_i2c_buf_t *bufs, unsigned int flags);

#endif // MICROPY_INCLUDED_MACHINE_I2C_H
