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
#include "hal_pz_i2c.h"
#if BUILD_BOARD == DASHIXIONG_BOARD


//static int8_t new_class_flag = 0;


typedef struct _device_motor_obj_t {
    mp_obj_base_t base;	
	uint8_t addr;
	uint8_t id;
	uint8_t motor1_dir;
	uint8_t motor2_dir;
	uint8_t motor1_speed;
	uint8_t motor2_speed;
} device_motor_obj_t;




MP_STATIC int device_motor_init(device_motor_obj_t *self_in, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
	device_motor_obj_t *self = MP_OBJ_TO_PTR(self_in);
	self->id = 0;
	self->addr = 0x10;
	self->motor1_dir = 0;
	self->motor2_dir = 0;
	self->motor1_speed = 0x00;
	self->motor2_speed = 0x00;
	uint8_t buf[3] = {0};
	/* 初始化i2c */
	int ret = hal_pz_i2c_init(self->id,400000);
	int ret1 = 0;
	if(ret == 0){
		/* 设置电机速度为0 */
		ret1 = hal_pz_i2c_write(self->id,self->addr,buf,3);
		if(ret1 == 0){
			/* 设置电机速度为0 */ 
			buf[0] = 0x02;
			ret1 = hal_pz_i2c_write(self->id,self->addr,buf,3);
		}
		if(ret1!=0){
			hal_pz_i2c_deinit(self->id);
			/* 写 i2c 数据没有反应,可能是没有链接上外扩板 */
			return -2; 
		}
	}
	return ret;
}





/******************************************************************************/
// MicroPython bindings for machine API
MP_STATIC void device_motor_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    //device_motor_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "df rotot motor driver");
}







mp_obj_t device_motor_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    mp_arg_check_num(n_args, n_kw, 0, 0, true);
	device_motor_obj_t *self = m_new_obj(device_motor_obj_t);
	if(self == NULL){
		mp_raise_msg(&mp_type_RuntimeError,MP_ERROR_TEXT("micropython run out of memory"));
	}
	self->base.type = type;
	self->id = 0;
	self->addr = 0x10;
	self->motor1_dir = 0;
	self->motor2_dir = 0;
	self->motor1_speed = 0x00;
	self->motor2_speed = 0x00;
	int ret = device_motor_init(self, n_args - 1, all_args + 1, NULL);
	if(ret==0){
    	return MP_OBJ_FROM_PTR(self);
	}else{
		mp_raise_msg(&mp_type_OSError, MP_ERROR_TEXT("External motors may not be connected! Please check!!!"));
		return mp_const_none;
	}
}





MP_STATIC mp_obj_t mp_device_motor_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    int ret = device_motor_init(args[0], n_args - 1, args + 1, kw_args);
	if(ret == 0){
		return mp_const_true;
	}else{
		mp_raise_msg(&mp_type_OSError, MP_ERROR_TEXT("External motors may not be connected! Please check!!!"));
		return mp_const_false;
	}
}
MP_DEFINE_CONST_FUN_OBJ_KW(mp_device_motor_init_obj, 1, mp_device_motor_init);





MP_STATIC mp_obj_t mp_device_motor_deinit(mp_obj_t self_in) {
	device_motor_obj_t *self = MP_OBJ_TO_PTR(self_in);
	hal_pz_i2c_deinit(self->id);
	return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_motor_deinit_obj, mp_device_motor_deinit);






int set_speed(device_motor_obj_t *self,int motor, int dir,int speed){
	int ret0=0, ret1=0;
	uint8_t buf[3] = {0x00,0x00,0x00};
	if(speed>255){
		speed = 255;
	}
	if(speed < 0){
		speed = 0;
	}
	if(motor == 0){
		self->motor1_dir = dir;
		self->motor1_speed = speed;
		buf[0] = 0x00;
		buf[1] = self->motor1_dir;
		buf[2] = self->motor1_speed;
		ret0 = hal_pz_i2c_write(self->id,self->addr,buf,3);
		return ret0;
	}else if(motor == 1){
		self->motor2_dir = dir;
		self->motor2_speed = speed;
		buf[0] = 0x02;
		buf[1] = self->motor2_dir;
		buf[2] = self->motor2_speed;
		ret1 = hal_pz_i2c_write(self->id,self->addr,buf,3);
		return ret1;
	}else{
		self->motor1_dir = dir;
		self->motor2_dir = dir;
		self->motor1_speed = speed;
		self->motor2_speed = speed;
		buf[0] = 0x00;
		buf[1] = self->motor1_dir;
		buf[2] = self->motor1_speed;
		ret0 = hal_pz_i2c_write(self->id,self->addr,buf,3);
		buf[0] = 0x02;
		buf[1] = self->motor2_dir;
		buf[2] = self->motor2_speed;
		ret1 = hal_pz_i2c_write(self->id,self->addr,buf,3);
		if(ret0 == 0x00 && ret1 == 0x00){
			return 0;
		}else{
			return -1;
		}
	}
}


MP_STATIC mp_obj_t mp_device_motor_speed(size_t n_args, const mp_obj_t *args) {
	device_motor_obj_t *self = MP_OBJ_TO_PTR(args[0]);
	if(n_args==4){
		
		/* 检查参数 */
		//mp_arg_check_num(n_args, 0, 4, 4, false);
		/* 获取motor */
		
		int motor = mp_obj_get_int(args[1]);
		int dir = mp_obj_get_int(args[2]);
		int speed = mp_obj_get_int(args[3]);
		int ret = set_speed(self,motor,dir,speed);
		if(ret == 0){
			return mp_const_true;
		}else{
			return mp_const_false;
		}
		/* 有多个参数，设置速度 */
	}else{
		/* 只有self则返回速度 */
		mp_obj_t tuple[4];
		tuple[0] = mp_obj_new_int(self->motor1_dir);
    	tuple[1] = mp_obj_new_int(self->motor1_speed);
		tuple[2] = mp_obj_new_int(self->motor2_dir);
		tuple[3] = mp_obj_new_int(self->motor2_speed);
    	return mp_obj_new_tuple(4, tuple);
	}
	
}



MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_device_motor_speed_obj, 1, 4, mp_device_motor_speed);




MP_STATIC mp_obj_t mp_device_stop(mp_obj_t self_in,mp_obj_t motor_in) {
    device_motor_obj_t *self = MP_OBJ_TO_PTR(self_in);
	int motor = mp_obj_get_int(motor_in);
	int ret = set_speed(self,motor,0x00,0x00);
	if(ret == 0){
    	return mp_const_true;
	}else{
		return mp_const_false;
	}
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_2(mp_device_motor_stop_obj, mp_device_stop);






MP_STATIC const mp_rom_map_elem_t device_motor_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mp_device_motor_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&mp_device_motor_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR_speed), MP_ROM_PTR(&mp_device_motor_speed_obj) },
    { MP_ROM_QSTR(MP_QSTR_stop), MP_ROM_PTR(&mp_device_motor_stop_obj) },
	
};
MP_DEFINE_CONST_DICT(mp_device_motor_locals_dict, device_motor_locals_dict_table);





const mp_obj_type_t device_motor_type = {
    { &mp_type_type },
    .name = MP_QSTR_DF_MOTOR,
    .print = device_motor_print,
    .make_new = device_motor_make_new,
    .locals_dict = (mp_obj_dict_t *)&mp_device_motor_locals_dict,
};


#endif

