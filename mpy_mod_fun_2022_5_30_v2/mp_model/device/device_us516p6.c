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
#include "device_us516p6.h"
#include "moddevice.h"
#include "modmachine.h"
#include "hal_pz_uart.h"

#if BUILD_BOARD == DASHIXIONG_BOARD
static const unsigned char uartWriteBuff[] = {"hello uart!"};
const unsigned char Wake_Up[] = {0x5A, 0xA5, 0x64, 0x73, 0x78, 0x5A};
const unsigned char LED_On[] = {0x5A, 0xA5, 0x02, 0x6F, 0x6E, 0x5A};
//const unsigned char LED_Off[] = {0x5A, 0xA5, 0x03, 0x6F, 0x66, 0x66, 0x5A};
//const unsigned char Bright_Up[] = {0x5A, 0xA5, 0x04, 0x62, 0x5F, 0x75, 0x70, 0x5A};
//const unsigned char Bright_Down[] = {0x5A, 0xA5, 0x06, 0x62, 0x5F, 0x64, 0x6F, 0x77, 0x6E, 0x5A};
const unsigned char Buzzer_On[]  = {0x5A, 0xA5, 0x04, 0x64, 0x6b, 0x62,0x6a, 0x5A};
const unsigned char Buzzer_Off[] = {0x5A, 0xA5, 0x04, 0x67, 0x62, 0x62,0x6a, 0x5A};


static int new_class_flag=0;

typedef struct _machine_us516p6_obj_t {
	mp_obj_base_t base;
	/* 阻塞标志 */
    int block_flag;
	/* 接收buf */
	uint8_t *recv_buf;
} machine_us516p6_obj_t;





MP_STATIC int CMP_Array(const unsigned char *Array_Local, unsigned char *Array_Remote, unsigned char num)

{
	for(unsigned char i = 0; i < num; i++ )
	{
		if(*Array_Local == *Array_Remote)
		{
			Array_Local++;		//比较下一个数组字符
			Array_Remote++;
		}
		else
		{
			return false;		//否则返回错误
			
		}
	
	}
	return true;		//所有字符比较结束，返回正确

}





MP_STATIC mp_obj_t mp_us516p6_recognition(mp_obj_t self_in) {
	int errcode = 0;
	int resoult = 0;
	mp_uint_t size = 16;
    machine_us516p6_obj_t *self = MP_OBJ_TO_PTR(self_in);
	/* 获取流 */
	
	int len = hal_pz_uart_read(1, self->recv_buf, size);
	if (len > 0) {
		#if 0
		if(true == CMP_Array(LED_On, self->recv_buf, sizeof(LED_On)/sizeof(LED_On[0]))){
			resoult = 2;
		}
        else if(true == CMP_Array(LED_Off, self->recv_buf, sizeof(LED_Off)/sizeof(LED_Off[0]))){
			resoult = 3;
        }
        else if(true == CMP_Array(Bright_Up, self->recv_buf, sizeof(Bright_Up)/sizeof(Bright_Up[0]))){
  			resoult = 4;
        }
        else if(true == CMP_Array(Bright_Down, self->recv_buf, sizeof(Bright_Down)/sizeof(Bright_Down[0]))){
			resoult = 5;
        }
        else if(true == CMP_Array(Wake_Up, self->recv_buf, sizeof(Wake_Up)/sizeof(Wake_Up[0]))){
			resoult = 1;
		}
		#endif
		if(true == CMP_Array(Wake_Up, self->recv_buf, sizeof(Wake_Up)/sizeof(Wake_Up[0]))){
			resoult = 1;
		}else if(true == CMP_Array(Buzzer_On, self->recv_buf, sizeof(Buzzer_On)/sizeof(Buzzer_On[0]))){
			resoult = 2;
		}else if(true == CMP_Array(Buzzer_Off, self->recv_buf, sizeof(Buzzer_Off)/sizeof(Buzzer_Off[0]))){
			resoult = 3;
		}
		
	}else{
		resoult= 0;
	}
	return mp_obj_new_int(resoult);
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_us516p6_recognition_obj, mp_us516p6_recognition);






/* 使用该接口时需要传入一个uart对象 */
MP_STATIC mp_obj_t machine_us516p6_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
	/*检查参数*/
	if(new_class_flag == 0){
		IotUartAttribute uart_cfg = {115200, 8, 1, IOT_UART_PARITY_NONE, 0, 0, 0};
		machine_us516p6_obj_t *self = m_new_obj(machine_us516p6_obj_t);
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
		self->base.type = &device_us516p6_type;
		if(self->block_flag){
			uart_cfg.rxBlock = IOT_UART_BLOCK_STATE_BLOCK;
		}
		int ret = hal_pz_uart_init(1,&uart_cfg);
		//printf("ret = %d\r\n",ret);
		if(ret == 0){
			new_class_flag = 1;
			hal_pz_uart_write(1, uartWriteBuff, (mp_uint_t)strlen(uartWriteBuff));
			return MP_OBJ_FROM_PTR(self);
		}else{
			return mp_const_none;
		}
	}
	/* 返回空对象 */
	return mp_const_none;
}







MP_STATIC void machine_us516p6_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    machine_us516p6_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "ASR us516p6 chip;uart interface!");
}






MP_STATIC const mp_rom_map_elem_t us516p6_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR_recognition), MP_ROM_PTR(&mp_us516p6_recognition_obj) },
};



MP_STATIC MP_DEFINE_CONST_DICT(mus516p6_locals_dict, us516p6_module_globals_table);






const mp_obj_type_t device_us516p6_type = {
    { &mp_type_type },
    .name = MP_QSTR_US516P6,
    .print = machine_us516p6_print,
    .make_new = machine_us516p6_make_new,
    .locals_dict = (mp_obj_dict_t *)&mus516p6_locals_dict,
};
#endif

