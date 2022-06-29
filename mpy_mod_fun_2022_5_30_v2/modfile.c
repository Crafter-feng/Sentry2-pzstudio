
#include "utils_file.h"
#include "py/compile.h"
typedef struct _mp_obj_file_t {
    mp_obj_base_t base;
    int fd;
    char *path;
    int size;
} mp_obj_file_t;
const mp_obj_type_t mp_type_file;

MP_STATIC mp_obj_file_t *file_new(int fd, char *path) {
    mp_obj_file_t *o = m_new_obj(mp_obj_file_t);
    o->base.type = &mp_type_file;
    o->fd = fd;
    o->path = path;
    int size = 0;
    int flag = UtilsFileStat(path,&size);
    o->size = size;
    return o;
}
mp_obj_t mp_builtin_open(mp_obj_t name, mp_obj_t open_mode) {
    char *filename = mp_obj_str_get_str(name);
    char *mode = mp_obj_str_get_str(open_mode);
    int mode_rw = 0, mode_x = 0;
    while (*mode) {
        switch (*mode++) {
            case 'r':
                mode_rw = O_RDONLY_FS;
                break;
            case 'w':
                mode_rw = O_WRONLY_FS;
                mode_x = O_CREAT_FS | O_TRUNC_FS;
                break;
            case 'a':
                mode_rw = O_WRONLY_FS;
                mode_x = O_CREAT_FS | O_APPEND_FS;
                break;
            case '+':
                mode_rw = O_RDWR_FS;
                break;
        }
    }
    int fd = UtilsFileOpen(filename, mode_x | mode_rw, 0);
    return MP_OBJ_FROM_PTR(file_new(fd,filename));
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_builtin_open_obj, mp_builtin_open);

mp_obj_t mp_builtin_write(mp_obj_t file, mp_obj_t content) {
    mp_obj_file_t *self = MP_OBJ_TO_PTR(file);
    mp_int_t fd = self->fd;
    char *mode = mp_obj_str_get_str(content);
    // printf("%s",mode);
    int len = UtilsFileWrite(fd, mode, strlen(mode));
    UtilsFileClose(fd);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_builtin_write_obj, mp_builtin_write);

// mp_obj_t mp_builtin_write(mp_obj_t file, mp_obj_t content) {
//     mp_obj_file_t *self = MP_OBJ_TO_PTR(file);
//     mp_int_t fd = self->fd;
//     char *mode = mp_obj_str_get_str(content);
//     int len = UtilsFileWrite(fd, mode, strlen(mode));
//     UtilsFileClose(fd);
//     return mp_const_none;
// }
// MP_DEFINE_CONST_FUN_OBJ_2(mp_builtin_write_obj, mp_builtin_write);

mp_obj_t mp_read(size_t n_args, const mp_obj_t *args) {
    mp_obj_file_t *self = MP_OBJ_TO_PTR(args[0]);
    mp_int_t fd = self->fd;
    if (n_args == 1){
        int len = self->size;
        int curSeek = UtilsFileSeek(fd, 0, SEEK_CUR_FS);
        len = len - curSeek;
        char *buf = (char*)malloc(sizeof(char)*len);
        int readlen = UtilsFileRead(fd,buf,len);
        mp_obj_t res = mp_obj_new_str(buf,len);
        free(buf);
        return res;
    }else if(n_args == 2){
        int filesize = self->size;
        int len = mp_obj_get_int(args[1]);
        int curSeek = UtilsFileSeek(fd, 0, SEEK_CUR_FS);
        if(curSeek + len > filesize - 1){
            len = filesize - curSeek;
        }
        char *buf = (char*)malloc(sizeof(char)*len);
        int readlen = UtilsFileRead(fd,buf,len);
        mp_obj_t res = mp_obj_new_str(buf,len);
        free(buf);
        return res;
    }
    // mp_obj_file_t *self = MP_OBJ_TO_PTR(file);
    // mp_int_t fd = self->fd;
    // char *mode = mp_obj_str_get_str(content);
    // int len = UtilsFileRead(fd, mode, strlen(mode));
    // UtilsFileClose(fd);
    // printf("param len = %d\r\n",n_args);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_VAR(mp_read_obj, 1, mp_read);

mp_obj_t mp_close(mp_obj_t file, mp_obj_t content) {
    mp_obj_file_t *self = MP_OBJ_TO_PTR(file);
    mp_int_t fd = self->fd;
    UtilsFileClose(fd);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_close_obj, mp_close);


mp_obj_t mp_seek(size_t n_args, const mp_obj_t *args) {
    mp_obj_file_t *self = MP_OBJ_TO_PTR(args[0]);
    mp_int_t fd = self->fd;
    int offset = mp_obj_get_int(args[1]);
    int whence = 0;
    if (n_args == 2){
        whence = 0;
    }else if(n_args == 3){
        whence = mp_obj_get_int(args[2]);
    }
    int pos  = UtilsFileSeek(fd, offset, whence);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_VAR(mp_seek_obj,2, mp_seek);


mp_obj_t mp_tell(mp_obj_t file) {
    mp_obj_file_t *self = MP_OBJ_TO_PTR(file);
    mp_int_t fd = self->fd;
    int pos  = UtilsFileSeek(fd, 0, SEEK_CUR_FS);
    return mp_obj_new_int(pos);
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_tell_obj, mp_tell);

MP_STATIC mp_obj_t file_make_new(mp_obj_t name, mp_obj_t open_mode) {
    char *filename = mp_obj_str_get_str(name);
    char *mode = mp_obj_str_get_str(open_mode);
    int mode_rw = 0, mode_x = 0;
    while (*mode) {
        switch (*mode++) {
            case 'r':
                mode_rw = O_RDONLY_FS;
                break;
            case 'w':
                mode_rw = O_WRONLY_FS;
                mode_x = O_CREAT_FS | O_TRUNC_FS;
                break;
            case 'a':
                mode_rw = O_WRONLY_FS;
                mode_x = O_CREAT_FS | O_APPEND_FS;
                break;
            case '+':
                mode_rw = O_RDWR_FS;
                break;
        }
    }
    int fd = UtilsFileOpen(filename, mode_x | mode_rw, 0);
    return MP_OBJ_FROM_PTR(file_new(fd,filename));
}


MP_STATIC const mp_rom_map_elem_t file_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_write), MP_ROM_PTR(&mp_builtin_write_obj) },
    { MP_ROM_QSTR(MP_QSTR_read), MP_ROM_PTR(&mp_read_obj) },
    { MP_ROM_QSTR(MP_QSTR_close), MP_ROM_PTR(&mp_close_obj) },
    { MP_ROM_QSTR(MP_QSTR_seek), MP_ROM_PTR(&mp_seek_obj) },
    { MP_ROM_QSTR(MP_QSTR_tell), MP_ROM_PTR(&mp_tell_obj) },
};
MP_STATIC MP_DEFINE_CONST_DICT(file_locals_dict, file_locals_dict_table);

const mp_obj_type_t mp_type_file = {
    { &mp_type_type },
    .name = MP_QSTR_file,
    .make_new = file_make_new,
    .getiter = NULL,
    .iternext = NULL,
    .locals_dict = (mp_obj_dict_t *)&file_locals_dict,
};