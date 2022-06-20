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





#if  (BUILD_BOARD == TQ_BOARD )||(BUILD_BOARD == DASHIXIONG_BOARD)
#include "aht2x.h"


static int8_t new_class_flag = 0;


typedef struct _device_thumi_temp_obj_t {
    mp_obj_base_t base;	
} device_thumi_temp_obj_t;




MP_STATIC int device_thumi_temp_init(device_thumi_temp_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
	int ret = tqs1_aht2x_init();
	return ret;
}





/******************************************************************************/
// MicroPython bindings for machine API
MP_STATIC void device_thumi_temp_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    device_thumi_temp_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "humiture temperature device");
}







mp_obj_t device_thumi_temp_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    mp_arg_check_num(n_args, n_kw, 0, 0, true);
	device_thumi_temp_obj_t *self = m_new_obj(device_thumi_temp_obj_t);
	if(self == NULL){
		mp_raise_msg(&mp_type_RuntimeError,MP_ERROR_TEXT("micropython run out of memory"));
	}
	self->base.type = &device_thumi_temp_type;
	int ret = device_thumi_temp_init(self, n_args - 1, all_args + 1, NULL);
	if(ret==0){
    	return MP_OBJ_FROM_PTR(self);
	}else{
		return mp_const_none;
	}
}





MP_STATIC mp_obj_t mp_device_thumi_temp_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    int ret = device_thumi_temp_init(args[0], n_args - 1, args + 1, kw_args);
	if(ret == 0){
		return mp_const_true;
	}else{
		return mp_const_false;
	}
}
MP_DEFINE_CONST_FUN_OBJ_KW(mp_device_thumi_temp_init_obj, 1, mp_device_thumi_temp_init);





MP_STATIC mp_obj_t mp_device_thumi_temp_deinit(mp_obj_t self_in) {
	
	return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_thumi_temp_deinit_obj, mp_device_thumi_temp_deinit);







MP_STATIC mp_obj_t mp_device_humi_temp_value(mp_obj_t self_in) {
    device_thumi_temp_obj_t *self = MP_OBJ_TO_PTR(self_in);
	float humi,temp;
	mp_obj_t tuple[2];

	int ret1 =  AHT20_StartMeasure();
	int ret = AHT20_GetMeasureResult(&temp,&humi);
	if(ret == 0 && ret1 == 0){
		tuple[0] = mp_obj_new_float(temp);
		tuple[1] = mp_obj_new_float(humi);
		return mp_obj_new_tuple(2, tuple);
	}
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_humi_temp_value_obj, mp_device_humi_temp_value);






MP_STATIC mp_obj_t mp_device_humi_temp_get_T(mp_obj_t self_in) {
    device_thumi_temp_obj_t *self = MP_OBJ_TO_PTR(self_in);
	float humi,temp;
	int ret1 =  AHT20_StartMeasure();
	int ret = AHT20_GetMeasureResult(&temp,&humi);
	if(ret == 0 && ret1 == 0){
		return mp_obj_new_float(temp);
	}
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_humi_temp_get_T_obj, mp_device_humi_temp_get_T);






MP_STATIC mp_obj_t mp_device_humi_temp_get_H(mp_obj_t self_in) {
    device_thumi_temp_obj_t *self = MP_OBJ_TO_PTR(self_in);
	float humi,temp;
	int ret1 =  AHT20_StartMeasure();
	int ret = AHT20_GetMeasureResult(&temp,&humi);
	if(ret == 0 && ret1 == 0){
		return mp_obj_new_float(humi);
	}
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_humi_temp_get_H_obj, mp_device_humi_temp_get_H);





MP_STATIC const mp_rom_map_elem_t device_thumi_temp_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mp_device_thumi_temp_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&mp_device_thumi_temp_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR_value), MP_ROM_PTR(&mp_device_humi_temp_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_temp), MP_ROM_PTR(&mp_device_humi_temp_get_T_obj) },
    { MP_ROM_QSTR(MP_QSTR_humi), MP_ROM_PTR(&mp_device_humi_temp_get_H_obj) },
};
MP_DEFINE_CONST_DICT(mp_device_thumi_temp_locals_dict, device_thumi_temp_locals_dict_table);





const mp_obj_type_t device_thumi_temp_type = {
    { &mp_type_type },
    .name = MP_QSTR_AHT2X,
    .print = device_thumi_temp_print,
    .make_new = device_thumi_temp_make_new,
    .locals_dict = (mp_obj_dict_t *)&mp_device_thumi_temp_locals_dict,
};


#endif


