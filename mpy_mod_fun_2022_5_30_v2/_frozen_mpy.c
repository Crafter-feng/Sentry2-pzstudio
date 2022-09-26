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



#include "py/mpconfig.h"
#include "py/objint.h"
#include "py/objstr.h"
#include "py/emitglue.h"
#include "py/nativeglue.h"

#if MICROPY_OPT_CACHE_MAP_LOOKUP_IN_BYTECODE != 0
#error "incompatible MICROPY_OPT_CACHE_MAP_LOOKUP_IN_BYTECODE"
#endif

#if MICROPY_LONGINT_IMPL != 0
#error "incompatible MICROPY_LONGINT_IMPL"
#endif

#if MICROPY_PY_BUILTINS_FLOAT
typedef struct _mp_obj_float_t {
    mp_obj_base_t base;
    mp_float_t value;
} mp_obj_float_t;
#endif

#if MICROPY_PY_BUILTINS_COMPLEX
typedef struct _mp_obj_complex_t {
    mp_obj_base_t base;
    mp_float_t real;
    mp_float_t imag;
} mp_obj_complex_t;
#endif

enum {
    MP_QSTR_frozentest_dot_py = MP_QSTRnumber_of,
    MP_QSTR_uos,
    MP_QSTR_bdev,
    MP_QSTR_flashbdev,
    MP_QSTR_inisetup,
    MP_QSTR_setup,
    MP_QSTR_vfs,
};

extern const qstr_pool_t mp_qstr_const_pool;
const qstr_pool_t mp_qstr_frozen_const_pool = {
    (qstr_pool_t*)&mp_qstr_const_pool, // previous pool
    MP_QSTRnumber_of, // previous pool size
    7, // allocated entries
    7, // used entries
    {
        (const byte*)"\xfe\x0d" "frozentest.py",
        (const byte*)"\xec\x03" "uos",
        (const byte*)"\x70\x04" "bdev",
        (const byte*)"\xc0\x09" "flashbdev",
        (const byte*)"\x0c\x08" "inisetup",
        (const byte*)"\xc2\x05" "setup",
        (const byte*)"\x86\x03" "vfs",
    },
};

// frozen bytecode for file frozentest.py, scope frozentest_<module>
MP_STATIC const byte fun_data_frozentest__lt_module_gt_[117] = {
    0x2c, 0x1a,
    MP_QSTR__lt_module_gt_ & 0xff, MP_QSTR__lt_module_gt_ >> 8,
    MP_QSTR_frozentest_dot_py & 0xff, MP_QSTR_frozentest_dot_py >> 8,
    0x28, 0x28, 0x50, 0x23, 0x26, 0x5b, 0x48, 0x4f, 0x00,
    0x80, 
    0x51, 
    0x1b, MP_QSTR_gc & 0xff, MP_QSTR_gc >> 8, 
    0x16, MP_QSTR_gc & 0xff, MP_QSTR_gc >> 8, 
    0x80, 
    0x51, 
    0x1b, MP_QSTR_uos & 0xff, MP_QSTR_uos >> 8, 
    0x16, MP_QSTR_uos & 0xff, MP_QSTR_uos >> 8, 
    0x80, 
    0x10, MP_QSTR_bdev & 0xff, MP_QSTR_bdev >> 8, 
    0x2a, 0x01, 
    0x1b, MP_QSTR_flashbdev & 0xff, MP_QSTR_flashbdev >> 8, 
    0x1c, MP_QSTR_bdev & 0xff, MP_QSTR_bdev >> 8, 
    0x16, MP_QSTR_bdev & 0xff, MP_QSTR_bdev >> 8, 
    0x59, 
    0x48, 0x18, 0x00, 
    0x11, MP_QSTR_bdev & 0xff, MP_QSTR_bdev >> 8, 
    0x44, 0x0f, 0x80, 
    0x11, MP_QSTR_uos & 0xff, MP_QSTR_uos >> 8, 
    0x14, MP_QSTR_mount & 0xff, MP_QSTR_mount >> 8, 
    0x11, MP_QSTR_bdev & 0xff, MP_QSTR_bdev >> 8, 
    0x10, MP_QSTR__slash_ & 0xff, MP_QSTR__slash_ >> 8, 
    0x36, 0x02, 
    0x59, 
    0x4a, 0x20, 0x00, 
    0x57, 
    0x11, MP_QSTR_OSError & 0xff, MP_QSTR_OSError >> 8, 
    0xdf, 
    0x44, 0x17, 0x80, 
    0x59, 
    0x80, 
    0x51, 
    0x1b, MP_QSTR_inisetup & 0xff, MP_QSTR_inisetup >> 8, 
    0x16, MP_QSTR_inisetup & 0xff, MP_QSTR_inisetup >> 8, 
    0x11, MP_QSTR_inisetup & 0xff, MP_QSTR_inisetup >> 8, 
    0x14, MP_QSTR_setup & 0xff, MP_QSTR_setup >> 8, 
    0x36, 0x00, 
    0x16, MP_QSTR_vfs & 0xff, MP_QSTR_vfs >> 8, 
    0x4a, 0x01, 0x00, 
    0x5d, 
    0x11, MP_QSTR_gc & 0xff, MP_QSTR_gc >> 8, 
    0x14, MP_QSTR_collect & 0xff, MP_QSTR_collect >> 8, 
    0x36, 0x00, 
    0x59, 
    0x51, 
    0x63, 
};
const mp_raw_code_t raw_code_frozentest__lt_module_gt_ = {
    .kind = MP_CODE_BYTECODE,
    .scope_flags = 0x00,
    .n_pos_args = 0,
    .fun_data = fun_data_frozentest__lt_module_gt_,
    .const_table = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 117,
    .n_obj = 0,
    .n_raw_code = 0,
    #if MICROPY_PY_SYS_SETTRACE
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name = MP_QSTR__lt_module_gt_,
        .qstr_source_file = MP_QSTR_frozentest_dot_py,
        .line_info = fun_data_frozentest__lt_module_gt_ + 6,
        .opcodes = fun_data_frozentest__lt_module_gt_ + 15,
    },
    .line_of_definition = 0,
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    .n_qstr = 0,
    .qstr_link = NULL,
    #endif
    #endif
    #if MICROPY_EMIT_MACHINE_CODE
    .type_sig = 0,
    #endif
};

const char mp_frozen_mpy_names[] = {
"frozentest.py\0"
"\0"};
const mp_raw_code_t *const mp_frozen_mpy_content[] = {
    &raw_code_frozentest__lt_module_gt_,
};
#ifdef MICROPY_FROZEN_LIST_ITEM
MICROPY_FROZEN_LIST_ITEM("frozentest", "frozentest.py")
#endif
