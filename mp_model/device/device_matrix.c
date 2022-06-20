#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "py/obj.h"
#include "py/runtime.h"
#include "py/stream.h"
#include "py/builtin.h"
#include "iot_gpio.h" 
#include <unistd.h>
#include "los_mux.h"
#include "moddevice.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "py/obj.h"
#include "py/runtime.h"
#include "matrixscreen.h"

static int8_t new_class_flag;


typedef struct _device_matrix_obj_t {
    mp_obj_base_t base;	
} device_matrix_obj_t;




MP_STATIC int device_matrix_init_helper(device_matrix_obj_t *self_in, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
	device_matrix_obj_t *self = MP_OBJ_TO_PTR(self_in);
	n_args = n_args;
	if(new_class_flag == 0){
		Init_MAX7219(14,9,10);
		new_class_flag = 1;		
		return 0;
	}else{
		return -1;
	}
	
}





mp_obj_t device_matrix_init(mp_obj_t self_in) {
	(void*)self_in;
    Init_MAX7219(14,9,10);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_matrix_init_obj, device_matrix_init);






mp_obj_t device_matrix_clear(mp_obj_t self_in) {
	(void*)self_in;
    matriOffall();
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_matrix_clear_obj, device_matrix_clear);

mp_obj_t device_matrix_showChar(mp_obj_t self_in,mp_obj_t c) {
    char *i = mp_obj_str_get_str(c);
    matriWriteString(i);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_matrix_showChar_obj, device_matrix_showChar);


mp_obj_t device_matrix_showString(mp_obj_t self_in,mp_obj_t c) {
    char *str_date = mp_obj_str_get_str(c);
    matriWriteString(str_date);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_matrix_showString_obj, device_matrix_showString);


mp_obj_t device_matrix_showMatrix(mp_obj_t self_in,mp_obj_t wr_buf){
	mp_buffer_info_t matrix;
	
    mp_get_buffer_raise(wr_buf, &matrix, MP_BUFFER_READ);
	if(matrix.len>0 && matrix.buf != NULL){
		matriShowdotMatrix(matrix.buf);
	}
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_matrix_showMatrix_obj, device_matrix_showMatrix);






mp_obj_t device_matrix_showDot(size_t n_args, const mp_obj_t *args){
	unsigned char* matrix_state =  getMatrixDate();
	int x = mp_obj_get_int(args[1]);
	int y = mp_obj_get_int(args[2]);
	int on_off = mp_obj_get_int(args[3]);
	if(x<=0 ){
		x = 1;
	}
	if(y <= 0){
		y = 1;
	}
	y = y-1;
	x = x-1;
	x=x%7;
	y=y%6;
	if(on_off==0){
		matrix_state[y] &= ((~(1<<(7-x-1)))&0x7f);
	}else{
		matrix_state[y] |= ((1<<(7-x-1))&0x7f);
	}	
	matriShowdotMatrix(matrix_state);
    return mp_const_none;
}


MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_matrix_showDot_obj, 4, 4, device_matrix_showDot);


MP_STATIC void device_matrix_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    mp_printf(print, "led matrix");
	
}



mp_obj_t device_matrix_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    mp_arg_check_num(n_args, n_kw, 0, 0, true);
	if(new_class_flag == 1){
		return mp_const_none;
	}
	device_matrix_obj_t *self = m_new_obj(device_matrix_obj_t);
	if(self == NULL){
		mp_raise_msg(&mp_type_RuntimeError,MP_ERROR_TEXT("micropython run out of memory"));
	}
	self->base.type = type;
	int ret = device_matrix_init_helper(self, n_args - 1, all_args + 1, NULL);
	if(ret==0){
		return MP_OBJ_FROM_PTR(self);
	}else{
		m_del_obj(device_matrix_obj_t,self);
		return mp_const_none;
	}
}






MP_STATIC const mp_rom_map_elem_t matrix_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_led) },
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mp_matrix_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_show_char), MP_ROM_PTR(&mp_matrix_showChar_obj) },
    { MP_ROM_QSTR(MP_QSTR_show_string), MP_ROM_PTR(&mp_matrix_showString_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear), MP_ROM_PTR(&mp_matrix_clear_obj) },
    { MP_ROM_QSTR(MP_QSTR_show_matrix), MP_ROM_PTR(&mp_matrix_showMatrix_obj) },
    { MP_ROM_QSTR(MP_QSTR_dot), MP_ROM_PTR(&mp_matrix_showDot_obj) },
};




MP_STATIC MP_DEFINE_CONST_DICT(matrix_module_globals, matrix_module_globals_table);



const mp_obj_type_t device_matrix_type = {
    { &mp_type_type },
    .name = MP_QSTR_MATRIX_SCREEN,
    .print = device_matrix_print,
    .make_new = device_matrix_make_new,
    .locals_dict = (mp_obj_dict_t *)&matrix_module_globals,
};


