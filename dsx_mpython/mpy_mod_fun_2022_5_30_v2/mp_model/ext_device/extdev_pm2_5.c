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
//#include "device_us516p6.h"
#include "mod_extdevice.h"
//#include "modmachine.h"
#include "hal_pz_uart.h"

#if BUILD_BOARD == DASHIXIONG_BOARD
static int new_class_flag=0;

typedef struct _extdev_pmxx_obj_t {
	mp_obj_base_t base;
	/* 阻塞标志 */
    int block_flag;
	/* 接收buf */
	uint8_t *recv_buf;
	uint16_t pm1_0;
	uint16_t pm2_5;
	uint16_t pm10;
} extdev_pmxx_obj_t;











MP_STATIC mp_obj_t extdev_pmxx_get_pm2_5(mp_obj_t self_in) {
	int errcode = 0;
	int resoult = 0;
	mp_uint_t size = 6;
    extdev_pmxx_obj_t *self = MP_OBJ_TO_PTR(self_in);
	/* 获取流 */
	//while(hal_pz_uart_read(2, self->recv_buf, 1)>0);
	uint8_t buf[]={0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
	hal_pz_uart_write(2, buf,sizeof(buf)/sizeof(buf[0]));
	self->recv_buf[0]= 0;
	while(hal_pz_uart_read(2, self->recv_buf, 2)>0){
		if(self->recv_buf[0]==0xff&&self->recv_buf[1]==0x86){
			break;
		}
	}
	
	
	int len = hal_pz_uart_read(2, self->recv_buf, size);
	if (len > 0) {
		if(len>=4){
			/*
			printf("recv<");
			for(int i=0; i<len; i++){
				printf("%x,",self->recv_buf[i]);
			}
			printf(">\r\n");*/
			self->pm2_5 = self->recv_buf[2]<<8|self->recv_buf[3];
			
		}
		
	}
	
	return mp_obj_new_int(self->pm2_5);
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(extdev_pmxx_get_pm2_5_obj, extdev_pmxx_get_pm2_5);






/* 使用该接口时需要传入一个uart对象 */
MP_STATIC mp_obj_t extdev_pmxx_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
	/*检查参数*/
	if(new_class_flag == 0){
		IotUartAttribute uart_cfg = {9600, 8, 1, IOT_UART_PARITY_NONE, 0, 0, 0};
		extdev_pmxx_obj_t *self = m_new_obj(extdev_pmxx_obj_t);
		if(self == NULL){
			mp_raise_msg(&mp_type_RuntimeError,MP_ERROR_TEXT("micropython run out of memory"));
		}
		mp_arg_check_num(n_args, n_kw, 0, 1, true);
		if(n_args == 0){
			self->block_flag = 0;
		}else if(n_args == 1){
			self->block_flag = mp_obj_get_int(args[0]);
		}	
		self->recv_buf = m_new(byte,16);
		if(self->recv_buf==NULL){
			mp_raise_msg(&mp_type_RuntimeError,MP_ERROR_TEXT("micropython run out of memory"));
		}
		self->base.type = type;
		if(self->block_flag){
			uart_cfg.rxBlock = IOT_UART_BLOCK_STATE_BLOCK;
		}
		int ret = hal_pz_uart_init(2,&uart_cfg);
		//printf("ret = %d\r\n",ret);
		if(ret == 0){
			new_class_flag = 1;
			/* 设置 pm2.5 为问答模式 */
			//hal_pz_uart_write(1, uartWriteBuff, (mp_uint_t)strlen(uartWriteBuff));
			uint8_t buf[]={0xFF,0x01,0x78,0x41,0x00,0x00,0x00,0x00,0x46};
			//uint8_t buf[]={0xFF,0x01,0x78,0x40,0x00,0x00,0x00,0x00,0x47};
			ret = hal_pz_uart_write(2, buf, sizeof(buf)/sizeof(buf[0]));
			printf("WRITE ret = %d\r\n",ret);
			return MP_OBJ_FROM_PTR(self);
		}else{
			return mp_const_none;
		}
	}
	/* 返回空对象 */
	return mp_const_none;
}







MP_STATIC void extdev_pmxx_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    extdev_pmxx_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "pm1.0 pm2.5 pm 10 mode,uart interface!");
}






MP_STATIC const mp_rom_map_elem_t extdev_pmxx_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR_get_pm2_5), MP_ROM_PTR(&extdev_pmxx_get_pm2_5_obj) },
};



MP_STATIC MP_DEFINE_CONST_DICT(extdev_pmxx_locals_dict, extdev_pmxx_module_globals_table);






const mp_obj_type_t extdev_pmxx_type = {
    { &mp_type_type },
    .name = MP_QSTR_PMxx,
    .print = extdev_pmxx_print,
    .make_new = extdev_pmxx_make_new,
    .locals_dict = (mp_obj_dict_t *)&extdev_pmxx_locals_dict,
};
#endif

