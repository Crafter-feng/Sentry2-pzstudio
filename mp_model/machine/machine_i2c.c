

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "py/mperrno.h"
#include "py/mphal.h"
#include "py/runtime.h"
#include "machine_i2c.h"
#include "hal_pz_i2c.h"
#include "modmachine.h"



typedef mp_machine_i2c_obj_t machine_i2c_obj_t;






// return value:
//  >=0 - success; for read it's 0, for write it's number of acks received
//   <0 - error, with errno being the negative of the return value
int mp_machine_i2c_transfer(mp_obj_base_t *self_in, uint16_t addr, size_t n, mp_machine_i2c_buf_t *bufs, unsigned int flags) {
    machine_i2c_obj_t *self = (machine_i2c_obj_t *)self_in;
	
	int transfer_ret = 0;
	for (; n--; ++bufs) {
		size_t len = bufs->len;
    	uint8_t *buf = bufs->buf;
		if (flags & MP_MACHINE_I2C_FLAG_READ){
			/* 读取数据 */
			transfer_ret = hal_pz_i2c_read(self->id,addr,buf,len);
			///printf("read transfer_ret = %x\r\n",transfer_ret);
		}else{
			/* 写数据 */
			//printf("addr = %d,self->id = %d\r\n",addr,self->id);
			//printf("<");
			//for(int i=0; i<len; i++){
			//	printf("0x%02x,",buf[i]);
			//}
			//printf(">\r\n");
			transfer_ret = hal_pz_i2c_write(self->id,addr,buf,len);
			//printf("write transfer_ret = %x\r\n",transfer_ret);
		}
	}
    return transfer_ret;
}






/******************************************************************************/
// Generic helper functions
// For use by ports that require a single buffer of data for a read/write transfer

MP_STATIC int mp_machine_i2c_readfrom(mp_obj_base_t *self, uint16_t addr, uint8_t *dest, size_t len, bool stop) {
    mp_machine_i2c_p_t *i2c_p = (mp_machine_i2c_p_t *)self->type->protocol;
    mp_machine_i2c_buf_t buf = {.len = len, .buf = dest};
    unsigned int flags = MP_MACHINE_I2C_FLAG_READ | (stop ? MP_MACHINE_I2C_FLAG_STOP : 0);
    return i2c_p->transfer(self, addr, 1, &buf, flags);
}






MP_STATIC int mp_machine_i2c_writeto(mp_obj_base_t *self, uint16_t addr, const uint8_t *src, size_t len, bool stop) {
    mp_machine_i2c_p_t *i2c_p = (mp_machine_i2c_p_t *)self->type->protocol;
    mp_machine_i2c_buf_t buf = {.len = len, .buf = (uint8_t *)src};
    unsigned int flags = stop ? MP_MACHINE_I2C_FLAG_STOP : 0;
    return i2c_p->transfer(self, addr, 1, &buf, flags);
}




/******************************************************************************/
// MicroPython bindings for generic machine.I2C
MP_STATIC mp_obj_t machine_i2c_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    mp_obj_base_t *self = (mp_obj_base_t *)MP_OBJ_TO_PTR(args[0]);
    mp_machine_i2c_p_t *i2c_p = (mp_machine_i2c_p_t *)self->type->protocol;
    if (i2c_p->init == NULL) {
        mp_raise_msg(&mp_type_OSError, MP_ERROR_TEXT("I2C operation not supported"));
    }
    i2c_p->init(self, n_args - 1, args + 1, kw_args);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(machine_i2c_init_obj, 1, machine_i2c_init);




MP_STATIC mp_obj_t machine_i2c_read(size_t n_args, const mp_obj_t *args) {
    mp_obj_base_t *self = (mp_obj_base_t *)MP_OBJ_TO_PTR(args[0]);
    mp_int_t addr = mp_obj_get_int(args[1]);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[2], &bufinfo, MP_BUFFER_WRITE);
    int ret = mp_machine_i2c_readfrom(self, addr, bufinfo.buf, bufinfo.len, false);
    if (ret < 0) {
        mp_raise_OSError(-ret);
    }
    return MP_OBJ_NEW_SMALL_INT(ret);
}
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(machine_i2c_read_obj, 3, 3, machine_i2c_read);



MP_STATIC mp_obj_t machine_i2c_write(size_t n_args, const mp_obj_t *args) {
    mp_obj_base_t *self = (mp_obj_base_t *)MP_OBJ_TO_PTR(args[0]);
    mp_int_t addr = mp_obj_get_int(args[1]);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[2], &bufinfo, MP_BUFFER_READ);
    int ret = mp_machine_i2c_writeto(self, addr, bufinfo.buf, bufinfo.len, 0);
    if (ret < 0) {
        mp_raise_OSError(-ret);
    }
	
    return MP_OBJ_NEW_SMALL_INT(ret);
}

MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(machine_i2c_write_obj, 3, 3, machine_i2c_write);








MP_STATIC const mp_rom_map_elem_t machine_i2c_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&machine_i2c_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_read), MP_ROM_PTR(&machine_i2c_read_obj) },
    { MP_ROM_QSTR(MP_QSTR_write), MP_ROM_PTR(&machine_i2c_write_obj) },
};
MP_DEFINE_CONST_DICT(mp_machine_i2c_locals_dict, machine_i2c_locals_dict_table);





/******************************************************************************/
// Implementation of soft I2C

MP_STATIC void mp_machine_i2c_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    mp_machine_i2c_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "I2C(id=%u, freq=%u)",self->id,self->freq);
}





MP_STATIC int mp_machine_i2c_init(mp_obj_base_t *self_in, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_freq};
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_freq, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 400000} },
    };
    mp_machine_i2c_obj_t *self = (mp_machine_i2c_obj_t *)self_in;
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);
	self->freq = args[ARG_freq].u_int;
	//printf("id = %d, freq = %d\r\n",self->id,self->freq);
	hal_pz_i2c_init(self->id,self->freq);
}






MP_STATIC mp_obj_t mp_machine_i2c_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    int ret  = 0;
    mp_arg_check_num(n_args, n_kw, 1, MP_OBJ_FUN_ARGS_MAX, true);
    machine_i2c_obj_t *self = m_new_obj(machine_i2c_obj_t);
	mp_int_t id = mp_obj_get_int(args[0]);
    self->base.type = &mp_machine_i2c_type;
	self->id = id;
    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    ret = mp_machine_i2c_init(self, n_args-1, args+1, &kw_args);
	if(ret == 0){
    	return MP_OBJ_FROM_PTR(self);
	}else{
		return mp_const_none;
	}
}





MP_STATIC const mp_machine_i2c_p_t mp_machine_i2c_p = {
    .init = mp_machine_i2c_init,
    .transfer = mp_machine_i2c_transfer,
};





const mp_obj_type_t mp_machine_i2c_type = {
    { &mp_type_type },
    .name = MP_QSTR_I2C,
    .print = mp_machine_i2c_print,
    .make_new = mp_machine_i2c_make_new,
    .protocol = &mp_machine_i2c_p,
    .locals_dict = (mp_obj_dict_t *)&mp_machine_i2c_locals_dict,
};




