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

#ifndef FILE_READER_H
#define FILE_READER_H

#include "py/compile.h"
#include "py/mperrno.h"

//mp_lexer_t* mp_lexer_new_from_file(const char* filename);
mp_import_stat_t mp_import_stat(const char* path);
void mp_reader_new_file(mp_reader_t* reader, const char* filename);
void mp_reader_new_file_from_fd(mp_reader_t* reader, int fd, bool close_fd);

#endif
