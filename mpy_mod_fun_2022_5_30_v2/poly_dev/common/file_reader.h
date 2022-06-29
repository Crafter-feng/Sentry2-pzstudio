

#ifndef FILE_READER_H
#define FILE_READER_H

#include "py/compile.h"
#include "py/mperrno.h"

//mp_lexer_t* mp_lexer_new_from_file(const char* filename);
mp_import_stat_t mp_import_stat(const char* path);
void mp_reader_new_file(mp_reader_t* reader, const char* filename);
void mp_reader_new_file_from_fd(mp_reader_t* reader, int fd, bool close_fd);

#endif
