#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <hi_types_base.h>
#include <hi_early_debug.h>
#include <hi_stdlib.h>
#include <hi_errno.h>
#include <hi_uart.h>
#include <hi_io.h>
#include "iot_gpio.h" 
#include "iot_uart.h" 
#include "hi_io.h"
#include "hi_gpio.h"
#include "iot_gpio.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/stream.h"
#include "py/mperrno.h"
#include "moddevice.h"
#include "parse_pin.h"
#if ((BUILD_BOARD == TQ_BOARD)||(BUILD_BOARD == DASHIXIONG_BOARD))


typedef struct _device_light_sen_obj_t {
    mp_obj_base_t base;
	uint8_t adc_ch;
} device_light_sen_obj_t;



MP_STATIC mp_obj_t device_light_sen_obj_init_helper(device_light_sen_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    
    return mp_const_none;
}



MP_STATIC mp_obj_t device_light_sen_obj_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
	return device_light_sen_obj_init_helper(args[0], n_args - 1, args + 1, kw_args);
}
MP_DEFINE_CONST_FUN_OBJ_KW(device_light_sen_init_obj, 1, device_light_sen_obj_init);




MP_STATIC mp_obj_t device_light_sen_value(size_t n_args, const mp_obj_t *args) {
    device_light_sen_obj_t *self = args[0];
	unsigned short adc_data = 0;
	if(hi_adc_read(self->adc_ch, &adc_data, HI_ADC_EQU_MODEL_4, HI_ADC_CUR_BAIS_DEFAULT, 0) != HI_ERR_SUCCESS){
			return mp_obj_new_int(0);
	}
	return MP_OBJ_NEW_SMALL_INT(adc_data);
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(device_light_sen_value_obj, 1, 1, device_light_sen_value);




MP_STATIC mp_obj_t device_light_sen_voltage(size_t n_args, const mp_obj_t *args) {
    device_light_sen_obj_t *self = args[0];
	unsigned short data = 0;
    int val = hi_adc_read(self->adc_ch,&data,HI_ADC_EQU_MODEL_4,HI_ADC_CUR_BAIS_AUTO,0);
	if(val == -1) {
        mp_raise_ValueError(MP_ERROR_TEXT("parameter error"));
    }
	float voltage =  hi_adc_convert_to_voltage(data);
    return mp_obj_new_float(voltage);
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(device_light_sen_voltage_obj, 1, 1, device_light_sen_voltage);




MP_STATIC void device_light_sen_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    device_light_sen_obj_t *self = self_in;
    mp_printf(print, "LIGHT SENSOR");
}




mp_obj_t mp_light_sen_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
	mp_arg_check_num(n_args, n_kw, 0, 0, true);
    device_light_sen_obj_t *self = m_new_obj(device_light_sen_obj_t);
	memset(self,0,sizeof(device_light_sen_obj_t));
	self->base.type = &device_light_sen_type;
#if (BUILD_BOARD == TQ_BOARD)
	self->adc_ch = HI_ADC_CHANNEL_6;
	//printf("TQ_BOARD\r\n");

#else
	self->adc_ch = HI_ADC_CHANNEL_5;
	//printf("DASHIXONG_BOARD\r\n");
#endif
	//printf("self->adc_ch = %d\r\n",self->adc_ch);
    //mp_map_t kw_args;
    //mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    //device_btn_obj_init_helper(self, n_args - 1, args + 1, &kw_args);
    return MP_OBJ_FROM_PTR(self);
}




MP_STATIC const mp_rom_map_elem_t device_light_sen_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&device_light_sen_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_value), MP_ROM_PTR(&device_light_sen_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_voltage), MP_ROM_PTR(&device_light_sen_voltage_obj) },
};



MP_STATIC MP_DEFINE_CONST_DICT(device_light_sen_locals_dict, device_light_sen_locals_dict_table);
const mp_obj_type_t device_light_sen_type = {
    { &mp_type_type },
    .name = MP_QSTR_LIGHT_SENSOR,
    .print = device_light_sen_print,
    .make_new = mp_light_sen_make_new,
    .locals_dict = (mp_obj_dict_t *)&device_light_sen_locals_dict,
};


#endif


