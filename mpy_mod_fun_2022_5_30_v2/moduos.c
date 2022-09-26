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
#include "extmod/vfs.h"
#include "dirent.h"
#include "libgen.h"

#include <stdio.h>
#include <string.h>
#include "sys/stat.h"
#include "fcntl.h"
#include "unistd.h"


        // "//kernel/liteos_m/components/fs/fatfs/fs.c",
        // "//kernel/liteos_m/components/fs/fatfs/fatfs.c",
// #include "stat.h"
/// \module os - basic "operating system" services
///
/// The `os` module contains functions for filesystem access and `urandom`.
///
/// The filesystem has `/` as the root directory, and the available physical
/// drives are accessible from here.  They are currently:
///
///     /flash      -- the internal flash filesystem
///     /sd         -- the SD card (if it exists)
///
/// On boot up, the current directory is `/flash` if no SD card is inserted,
/// otherwise it is `/sd`.
// MP_STATIC mp_obj_t os_listdir(void)
// {
//     return NULL;
// }
// MP_STATIC MP_DEFINE_CONST_FUN_OBJ_0(os_listdir_obj, os_listdir);
MP_STATIC const mp_rom_map_elem_t os_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_os) },
    { MP_ROM_QSTR(MP_QSTR_listdir), MP_ROM_PTR(&mp_vfs_listdir_obj) },
};


// mp_obj_t mp_listdir(size_t n_args, const mp_obj_t *args) {
//     int ret = mkdir("hello", 0777);
//     if (ret != 0) {
//         printf("mkdir failed.\n");
//     }
//     // mp_obj_t dir_list = mp_obj_new_list(0, NULL);
//     // char *dirname = {'.'};
//     // if (n_args == 0){
//     //     dirname = 0;
//     // }else if(n_args == 1){
//     //     dirname = mp_obj_str_get_str(args[0]);
//     // }
//     // DIR *dir = opendir(dirname);
//     // struct dirent *d = readdir(dir);
//     // // mp_obj_list_append
//     // return dir_list;
//     return mp_const_none;
    
// }
// MP_DEFINE_CONST_FUN_OBJ_VAR(mp_listdir_obj, 0, mp_listdir);

// MP_STATIC const mp_rom_map_elem_t os_module_globals_table[] = {
//     { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_os) },
//     { MP_ROM_QSTR(MP_QSTR_listdir), MP_ROM_PTR(&mp_listdir_obj) },
// };


MP_STATIC MP_DEFINE_CONST_DICT(os_module_globals, os_module_globals_table);

const mp_obj_module_t mp_module_os = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&os_module_globals,
};
