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
#include "modmachine.h"

#if BUILD_BOARD == DASHIXIONG_BOARD
#include "icm.h"

static int8_t new_class_flag = 0;


typedef struct _device_imu_obj_t {
    mp_obj_base_t base;	
} device_imu_obj_t;




MP_STATIC int device_imu_init(device_imu_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
	int ret = icm_initialize();
	return ret;
}





/******************************************************************************/
// MicroPython bindings for machine API
MP_STATIC void device_imu_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    device_imu_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "imu device(icm40607)");
}







mp_obj_t device_imu_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    mp_arg_check_num(n_args, n_kw, 0, 0, true);
	device_imu_obj_t *self = m_new_obj(device_imu_obj_t);
	if(self == NULL){
		mp_raise_msg(&mp_type_RuntimeError,MP_ERROR_TEXT("micropython run out of memory"));
	}
	self->base.type = &device_imu_type;
	int ret = device_imu_init(self, n_args - 1, all_args + 1, NULL);
	if(ret==0){
    	return MP_OBJ_FROM_PTR(self);
	}else{
		return mp_const_none;
	}
}





MP_STATIC mp_obj_t mp_device_imu_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    int ret = device_imu_init(args[0], n_args - 1, args + 1, kw_args);
	if(ret == 0){
		return mp_const_true;
	}else{
		return mp_const_false;
	}
}
MP_DEFINE_CONST_FUN_OBJ_KW(mp_device_imu_init_obj, 1, mp_device_imu_init);





MP_STATIC mp_obj_t mp_device_imu_deinit(mp_obj_t self_in) {
	
	return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_imu_deinit_obj, mp_device_imu_deinit);







MP_STATIC mp_obj_t mp_device_imu_read_acc(mp_obj_t self_in) {
    device_imu_obj_t *self = MP_OBJ_TO_PTR(self_in);
	byte * buf = m_new(byte, 12);
	mp_obj_t tuple[3];
	int ret = read_values(buf);
	
	if(ret == 0){
		tuple[0] = mp_obj_new_float(((int16_t)((buf[0]<<8)|buf[1]))/32767.0);
    	tuple[1] = mp_obj_new_float((((int16_t)(buf[2]<<8)|buf[3]))/32767.0);
		tuple[2] = mp_obj_new_float((((int16_t)(buf[4]<<8)|buf[5]))/32767.0);
		m_free(buf);
    	return mp_obj_new_tuple(3, tuple);
	}
	m_free(buf);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_imu_read_acc_obj, mp_device_imu_read_acc);






MP_STATIC mp_obj_t mp_device_imu_read_gyro(mp_obj_t self_in) {
    device_imu_obj_t *self = MP_OBJ_TO_PTR(self_in);
	byte * buf = m_new(byte, 12);
	mp_obj_t tuple[3];
	int ret = read_values(buf);
	if(ret == 0){
		tuple[0] = mp_obj_new_float(((int16_t)((buf[6]<<8)|buf[7]))*0.001064);
    	tuple[1] = mp_obj_new_float(((int16_t)((buf[8]<<8)|buf[9]))*0.001064);
		tuple[2] = mp_obj_new_float(((int16_t)((buf[10]<<8)|buf[11]))*0.001064);
		m_free(buf);
    	return mp_obj_new_tuple(3, tuple);
	}
	m_free(buf);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_imu_read_gyro_obj, mp_device_imu_read_gyro);




MP_STATIC mp_obj_t mp_device_imu_read_angle(mp_obj_t self_in) {
    byte * buf = m_new(byte, 12);
	mp_obj_t tuple[3];
	int ret = read_values(buf);
	if(ret == 0){
		tuple[0] = mp_obj_new_int(0);
    	tuple[1] = mp_obj_new_int(0);
		tuple[2] = mp_obj_new_int(0);
		m_free(buf);
    	return mp_obj_new_tuple(3, tuple);
	}
	m_free(buf);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_imu_read_angle_obj, mp_device_imu_read_angle);






MP_STATIC const mp_rom_map_elem_t device_imu_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mp_device_imu_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&mp_device_imu_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR_acc), MP_ROM_PTR(&mp_device_imu_read_acc_obj) },
    { MP_ROM_QSTR(MP_QSTR_gyro), MP_ROM_PTR(&mp_device_imu_read_gyro_obj) },
    { MP_ROM_QSTR(MP_QSTR_angle), MP_ROM_PTR(&mp_device_imu_read_angle_obj) },
};
MP_DEFINE_CONST_DICT(mp_device_imu_locals_dict, device_imu_locals_dict_table);





const mp_obj_type_t device_imu_type = {
    { &mp_type_type },
    .name = MP_QSTR_IMU,
    .print = device_imu_print,
    .make_new = device_imu_make_new,
    .locals_dict = (mp_obj_dict_t *)&mp_device_imu_locals_dict,
};






#elif  BUILD_BOARD == TQ_BOARD
#include "sc7a20.h"

static int8_t new_class_flag = 0;


typedef struct _device_imu_obj_t {
    mp_obj_base_t base;	
} device_imu_obj_t;




MP_STATIC int device_imu_init(device_imu_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
	int ret = SC7A20_Init();
	return ret;
}





/******************************************************************************/
// MicroPython bindings for machine API
MP_STATIC void device_imu_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    device_imu_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "imu device");
}







mp_obj_t device_imu_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    mp_arg_check_num(n_args, n_kw, 0, 0, true);
	device_imu_obj_t *self = m_new_obj(device_imu_obj_t);
	if(self == NULL){
		mp_raise_msg(&mp_type_RuntimeError,MP_ERROR_TEXT("micropython run out of memory"));
	}
	self->base.type = &device_imu_type;
	int ret = device_imu_init(self, n_args - 1, all_args + 1, NULL);
	if(ret==0){
    	return MP_OBJ_FROM_PTR(self);
	}else{
		return mp_const_none;
	}
}





MP_STATIC mp_obj_t mp_device_imu_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    int ret = device_imu_init(args[0], n_args - 1, args + 1, kw_args);
	if(ret == 0){
		return mp_const_true;
	}else{
		return mp_const_false;
	}
}
MP_DEFINE_CONST_FUN_OBJ_KW(mp_device_imu_init_obj, 1, mp_device_imu_init);





MP_STATIC mp_obj_t mp_device_imu_deinit(mp_obj_t self_in) {
	
	return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_imu_deinit_obj, mp_device_imu_deinit);




MP_STATIC mp_obj_t mp_device_imu_read_acc(mp_obj_t self_in) {
    device_imu_obj_t *self = MP_OBJ_TO_PTR(self_in);
	byte * buf = m_new(byte, 12);
	mp_obj_t tuple[3];
	//int ret = read_values(buf);
	int32_t *acc = SC7A20_GetInfo();
	if(acc != NULL){
		tuple[0] = mp_obj_new_float((acc[0]/16383.5));
    	tuple[1] = mp_obj_new_float((acc[1]/16383.5));
		tuple[2] = mp_obj_new_float((acc[2]/16383.5));
		m_free(buf);
    	return mp_obj_new_tuple(3, tuple);
	}
	m_free(buf);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_imu_read_acc_obj, mp_device_imu_read_acc);





#if 0
MP_STATIC mp_obj_t mp_device_imu_read_gyro(mp_obj_t self_in) {
    device_imu_obj_t *self = MP_OBJ_TO_PTR(self_in);
	byte * buf = m_new(byte, 12);
	mp_obj_t tuple[3];
	int ret = read_values(buf);
	if(ret == 0){
		tuple[0] = mp_obj_new_int((buf[6]<<8)|buf[7]);
    	tuple[1] = mp_obj_new_int((buf[8]<<8)|buf[9]);
		tuple[2] = mp_obj_new_int((buf[10]<<8)|buf[11]);
		m_free(buf);
    	return mp_obj_new_tuple(3, tuple);
	}
	m_free(buf);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_imu_read_gyro_obj, mp_device_imu_read_gyro);

#endif


MP_STATIC mp_obj_t mp_device_imu_read_angle(mp_obj_t self_in) {
    byte * buf = m_new(byte, 12);
	mp_obj_t tuple[3];
	int ret = read_values(buf);
	if(ret == 0){
		tuple[0] = mp_obj_new_int(0);
    	tuple[1] = mp_obj_new_int(0);
		tuple[2] = mp_obj_new_int(0);
		m_free(buf);
    	return mp_obj_new_tuple(3, tuple);
	}
	m_free(buf);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_imu_read_angle_obj, mp_device_imu_read_angle);






MP_STATIC const mp_rom_map_elem_t device_imu_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mp_device_imu_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&mp_device_imu_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR_acc), MP_ROM_PTR(&mp_device_imu_read_acc_obj) },
    //{ MP_ROM_QSTR(MP_QSTR_gyro), MP_ROM_PTR(&mp_device_imu_read_gyro_obj) },
    { MP_ROM_QSTR(MP_QSTR_angle), MP_ROM_PTR(&mp_device_imu_read_angle_obj) },
};
MP_DEFINE_CONST_DICT(mp_device_imu_locals_dict, device_imu_locals_dict_table);





const mp_obj_type_t device_imu_type = {
    { &mp_type_type },
    .name = MP_QSTR_IMU,
    .print = device_imu_print,
    .make_new = device_imu_make_new,
    .locals_dict = (mp_obj_dict_t *)&mp_device_imu_locals_dict,
};


#endif


