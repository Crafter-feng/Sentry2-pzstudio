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
#include "hi_time.h"
#include "iot_gpio.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/stream.h"
#include "py/mperrno.h"
#include "mod_extdevice.h"
#include "parse_pin.h"
#include "cmsis_os2.h" 
#include "extdev_ttp229.h"



#if 0


uint8_t ReadKey8(extdev_ttp229_obj_t *self)
{
	WaitForTouch(self);
	Key8(self);
	return self->_key8;
}



uint8_t GetKey8(extdev_ttp229_obj_t *self)
{
	if (IsTouch(self)) Key8(self);
	return self->_key8;
}



uint8_t ReadKeys8(extdev_ttp229_obj_t *self)
{
	WaitForTouch(self);
	Keys8(self);
	return self->_keys8;
}



uint8_t GetKeys8(extdev_ttp229_obj_t *self)
{
	if (IsTouch(self)) Keys8(self);
	return self->_keys8;
}



uint8_t ReadKey16(extdev_ttp229_obj_t *self)
{
	WaitForTouch(self);
	Key16(self);
	return self->_key16;
}



uint8_t GetKey16(extdev_ttp229_obj_t *self)
{
	if (IsTouch(self)) Key16(self);
	return self->_key16;
}




uint16_t ReadKeys16(extdev_ttp229_obj_t *self)
{
	WaitForTouch(self);
	Keys16(self);
	return self->_keys16;
}



uint16_t GetKeys16(extdev_ttp229_obj_t *self)
{
	if (IsTouch(self)) Keys16(self);
	return self->_keys16;
}




void Key8(extdev_ttp229_obj_t *self)
{
	self->_key8 = 0;
	for (uint8_t i = 0; i < 8; i++)
		if (GetBit(self)) self->_key8 = i + 1;
	hi_sleep(2); // Tout
}




void Keys8(extdev_ttp229_obj_t *self)
{
	self->_keys8 = 0;
	for (uint8_t i = 0; i < 8; i++)
		if (GetBit(self)) self->_keys8 |= 1 << i;
	hi_sleep(2); // Tout
}




void Key16(extdev_ttp229_obj_t *self)
{
	self->_key16 = 0;
	for (uint8_t i = 0; i < 16; i++)
		if (GetBit(self)) self->_key16 = i + 1;
	hi_sleep(2); // Tout
}




void Keys16(extdev_ttp229_obj_t *self)
{
	self->_keys16 = 0;
	for (uint8_t i = 0; i < 16; i++)
		if (GetBit(self)) self->_keys16 |= 1 << i;
	hi_sleep(2); // Tout
}




bool GetBit(extdev_ttp229_obj_t *self)
{
	IotGpioValue val = 0;
	IoTGpioSetOutputVal(self->scl_pin.gpio_id, 0);
	hi_udelay(2); // 500KHz
	IoTGpioGetInputVal(self->sdo_pin.gpio_id,&val);
	bool retVal = !val;
	IoTGpioSetOutputVal(self->scl_pin.gpio_id, 1);
	hi_udelay(2); // 500KHz
	return retVal;
}





bool IsTouch(extdev_ttp229_obj_t *self)
{
	uint16_t timeout = 5000; // 50ms timeout
	IotGpioValue val = 0;
	IoTGpioGetInputVal(self->sdo_pin.gpio_id,&val);
	
	while (val) // DV LOW
	{
		IoTGpioGetInputVal(self->sdo_pin.gpio_id,&val);
		if (--timeout == 0) return false;
		hi_udelay(10);
	}
	IoTGpioGetInputVal(self->sdo_pin.gpio_id,&val);
	
	while (!val) // DV HIGH
	{
		IoTGpioGetInputVal(self->sdo_pin.gpio_id,&val);
		if (--timeout == 0) return false;
		hi_udelay(10);
	}
	hi_udelay(10); // Tw
	return true;
}






void WaitForTouch(extdev_ttp229_obj_t *self)
{
	IotGpioValue val = 0;
	do { // DV LOW
		IoTGpioGetInputVal(self->sdo_pin.gpio_id,&val);
	}while(val);
	
	do { // DV HIGH
		IoTGpioGetInputVal(self->sdo_pin.gpio_id,&val);
	}while((!val));
	hi_udelay(10); // Tw
}



#else

#if 0

enum State {
  Waiting = 0, // Waiting for keypress and Data Valid signal from touchpad
  DataCooking, // Got Data Valid signal start, now waiting for Data Valid signal end
  DataReady    // Got properly timed Data Valid signal end, so we can now read which key was pressed
};

static int _extint;

static volatile enum State state;
static unsigned int buttonMap[16];
static volatile unsigned int buttonMask;
static unsigned long cookingTime;





uint32_t ttp229_get_time(){
	uint64_t tickCount = LOS_TickCountGet();
    return LOS_Tick2MS(tickCount);
	
}

void onFall(char *arg)
{
	extdev_ttp229_obj_t *self = (extdev_ttp229_obj_t *)arg;
	
	state = DataReady;
	IoTGpioUnregisterIsrFunc(self->sdo_pin.gpio_id);
	printf("1\r\n");
}



void onRise(char *arg)
{
	extdev_ttp229_obj_t *self = (extdev_ttp229_obj_t *)arg;
	state = DataCooking;
	cookingTime = ttp229_get_time();
	
	IoTGpioUnregisterIsrFunc(self->sdo_pin.gpio_id);

	IoTGpioRegisterIsrFunc(self->sdo_pin.gpio_id,IOT_INT_TYPE_EDGE,IOT_GPIO_EDGE_FALL_LEVEL_LOW,onFall,self);
}










uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
    uint8_t value = 0;
    uint8_t i;
	IotGpioValue val = 0;
    for(i = 0; i < 8; ++i) {
        if(bitOrder == 0){
			IoTGpioGetInputVal(dataPin,&val);
            value |= (val&0x01) << i;
        }
        else{
			IoTGpioGetInputVal(dataPin,&val);
            value |= ((val&0x01) << (7 - i));
        }
        IoTGpioSetOutputVal(clockPin, 1);
        IoTGpioSetOutputVal(clockPin, 0);
    }
    return value;
}




bool checkKeyState(extdev_ttp229_obj_t *self) {
	switch (state) {
		case Waiting:
		{
			break;
		}
		case DataCooking:
		{
			unsigned long checkTime = ttp229_get_time();
			if (checkTime - cookingTime > 150)
			{
				IoTGpioUnregisterIsrFunc(self->sdo_pin.gpio_id);
				state = Waiting;
				IoTGpioRegisterIsrFunc(self->sdo_pin.gpio_id,IOT_INT_TYPE_EDGE,IOT_GPIO_EDGE_RISE_LEVEL_HIGH,onRise,self);
			}
			break;
		}
		case DataReady:
		{
			unsigned int first = shiftIn(self->sdo_pin.gpio_id, self->scl_pin.gpio_id, 1);
			unsigned int second = shiftIn(self->sdo_pin.gpio_id, self->scl_pin.gpio_id, 1);
			buttonMask = (first << 8) + second;

			printf("buttonMask = %x\r\n",buttonMask);
			if (buttonMask > 0) {
				for (int i = 0; i < 16; i++)
				{
					if (buttonMask == buttonMap[i])
					{
						printf("button <%d> pressed",i+1);
					}
				}
			} else {
				
			}
			state = Waiting;
			IoTGpioRegisterIsrFunc(self->sdo_pin.gpio_id,IOT_INT_TYPE_EDGE,IOT_GPIO_EDGE_RISE_LEVEL_HIGH,onRise,self);
			break;
		}
	}
	return 0;
}

unsigned int getKeysPressed() {
	return buttonMask;
}
#endif
#endif

#if BUILD_BOARD == DASHIXIONG_BOARD

uint16_t TouchKey_Read(extdev_ttp229_obj_t *self)
{
    uint8_t i;
    uint16_t re_val = 0;
	IoTGpioSetDir(self->sdo_pin.gpio_id,HI_GPIO_DIR_OUT);
	IoTGpioSetOutputVal(self->sdo_pin.gpio_id,1);
	hi_udelay(100);
	IoTGpioSetOutputVal(self->sdo_pin.gpio_id,0); 
	hi_udelay(20);
	IoTGpioSetDir(self->sdo_pin.gpio_id,HI_GPIO_DIR_IN);
	for (i = 0; i < 16; i++)
	{
	    IoTGpioSetOutputVal(self->scl_pin.gpio_id,1);
		hi_udelay(200);
	    IoTGpioSetOutputVal(self->scl_pin.gpio_id,0);
		IotGpioValue val = 0;
		IoTGpioGetInputVal(self->sdo_pin.gpio_id,&val);
	    if (val!=0)
	    {
	       re_val |= (1 << i);
	    }
	    hi_udelay(200);
	}
    hi_sleep(2);    //根据时序图延时2ms， 不然容易出现按键串扰现象
    return re_val;
}







MP_STATIC int extdev_ttp229_obj_init_helper(extdev_ttp229_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
	enum { ARG_scl, ARG_sdo };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_scl, MP_ARG_INT, {.u_int = -1}},
        { MP_QSTR_sdo, MP_ARG_INT, {.u_int = -1}},
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);
	//printf("args[ARG_scl].u_int = %d, args[ARG_sdo].u_int = %d\r\n",args[ARG_scl].u_int,args[ARG_sdo].u_int);
	if(args[ARG_scl].u_int != -1){
		/* scl是关键字参数 */
		s_pin parse_pin = parse_single_pin(args[ARG_scl].u_int);
		if(parse_pin.gpio_aux.gpio_id != HI_GPIO_IDX_MAX){
			self->scl_pin = parse_pin.gpio_aux;
		}
	}else{
		if(self->scl_pin.gpio_id == HI_GPIO_IDX_MAX){
			s_pin parse_pin = parse_single_pin(15);
			if(parse_pin.gpio_aux.gpio_id != HI_GPIO_IDX_MAX){
				self->scl_pin = parse_pin.gpio_aux;
			}
		}
	}
	if(args[ARG_sdo].u_int != -1){
		s_pin parse_pin = parse_single_pin(args[ARG_sdo].u_int);
		if(parse_pin.gpio_aux.gpio_id != HI_GPIO_IDX_MAX){
			self->sdo_pin = parse_pin.gpio_aux;
		}
	}else{
		if(self->scl_pin.gpio_id == HI_GPIO_IDX_MAX){
			s_pin parse_pin = parse_single_pin(16);
			if(parse_pin.gpio_aux.gpio_id != HI_GPIO_IDX_MAX){
				self->sdo_pin = parse_pin.gpio_aux;
			}
		}
	}
	/* 初始化gpio口 */
	//pinMode(SCLPin , OUTPUT);
	IoTGpioDeinit(self->scl_pin.gpio_id);
	IoTGpioInit(self->scl_pin.gpio_id);
	IoTGpioDeinit(self->sdo_pin.gpio_id);
	IoTGpioInit(self->sdo_pin.gpio_id);
	
	hi_io_set_func(self->scl_pin.gpio_id,self->scl_pin.func);
  	//pinMode(SDOPin , INPUT);
	hi_io_set_func(self->sdo_pin.gpio_id,self->sdo_pin.func);
	IoTGpioSetDir(self->scl_pin.gpio_id,HI_GPIO_DIR_OUT);
	IoTGpioSetDir(self->sdo_pin.gpio_id,HI_GPIO_DIR_OUT);
	//hi_io_set_pull(self->scl_pin.gpio_id, HI_IO_PULL_DOWN);
	
	//hi_io_set_pull(self->sdo_pin.gpio_id, HI_IO_PULL_DOWN);
	IoTGpioSetOutputVal(self->scl_pin.gpio_id,0);
	IoTGpioSetOutputVal(self->sdo_pin.gpio_id,0);
	TouchKey_Read(self);
	
	
	return 0;
}







MP_STATIC mp_obj_t extdev_ttp229_obj_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
	extdev_ttp229_obj_t *self = args[0];
	extdev_ttp229_obj_init_helper(self, n_args - 1, args + 1, kw_args);
	return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(extdev_servo_obj_init_obj, 3, extdev_ttp229_obj_init);







MP_STATIC mp_obj_t extdev_get_key(size_t n_args, const mp_obj_t *args) {
	extdev_ttp229_obj_t *self = args[0];
	uint32_t key_data = TouchKey_Read(self);//ReadKeys16(self);
	return MP_OBJ_NEW_SMALL_INT(key_data);
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(extdev_get_key_obj, 1, 1, extdev_get_key);






MP_STATIC void extdev_ttp229_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    extdev_ttp229_obj_t *self = self_in;
    mp_printf(print, "ttp229 device driver");
	
}





mp_obj_t extdev_ttp229_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 2, 2, true);
	extdev_ttp229_obj_t *self = m_new_obj(extdev_ttp229_obj_t);
	memset(self,0,sizeof(extdev_ttp229_obj_t));
	self->scl_pin.gpio_id = HI_GPIO_IDX_MAX;
	
	self->sdo_pin.gpio_id = HI_GPIO_IDX_MAX;
	
	self->base.type = &extdev_ttp229_type;
    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    int ret = extdev_ttp229_obj_init_helper(self, n_args , args , &kw_args);
	if(ret==0){
    	return MP_OBJ_FROM_PTR(self);
	}else{
		return mp_const_none;
	}
}







MP_STATIC const mp_rom_map_elem_t extdev_ttp229_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&extdev_servo_obj_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_key), MP_ROM_PTR(&extdev_get_key_obj) },
};




MP_STATIC MP_DEFINE_CONST_DICT(extdev_ttp229_locals_dict, extdev_ttp229_locals_dict_table);

const mp_obj_type_t extdev_ttp229_type = {
    { &mp_type_type },
    .name = MP_QSTR_Ttp229,
    .print = extdev_ttp229_print,
    .make_new = extdev_ttp229_make_new,
    .locals_dict = (mp_obj_dict_t *)&extdev_ttp229_locals_dict,
};
#endif














#if 0
#include "TTP229.h"

ST_KEY_MAP em_ir_keymap[16] = {
  {"1", 0xFFFE},
  {"2", 0xFFFD},
  {"3", 0xFFFB},
  {"4", 0xFFEF},
  {"5", 0xFFDF},
  {"6", 0xFFBF},
  {"7", 0xFEFF},
  {"8", 0xFDFF},
  {"9", 0xFBFF},
  {"*", 0xEFFF},
  {"0", 0xDFFF},
  {"#", 0xBFFF},
  {"D", 0x7FFF},
  {"C", 0xF7FF},
  {"B", 0xFF7F},
  {"A", 0xFFF7},
};

void TTP229::initTTP229(uint8_t SclPin, uint8_t SdoPin) {
  SCLPin = SclPin;
  SDOPin = SdoPin;
  pinMode(SCLPin , OUTPUT);
  pinMode(SDOPin , INPUT);
}

uint16_t TTP229::GetKeyCode(void) {
  unsigned int DATA = 0;
  pinMode(SDOPin , OUTPUT);
  digitalWrite(SDOPin, HIGH);
  delayMicroseconds(93);
  digitalWrite(SDOPin, LOW);
  delayMicroseconds(10);
  pinMode(SDOPin , INPUT);
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(SCLPin, HIGH);
    digitalWrite(SCLPin, LOW);
    DATA |= digitalRead(SDOPin) << i;
  }
  delay(4);
  return DATA & 0xFFFF;
}



String TTP229::GetKeyMap(void) {
  byte i;
  uint16_t keycode = GetKeyCode();
  ST_KEY_MAP *irkeymap = em_ir_keymap;
  for (i = 0; i < KEY_MAX; i++) {
    //    Serial.println(irkeymap[i].keycode);
    if (irkeymap[i].keycode == keycode)
      return irkeymap[i].keyname;
  }
  return "";
}



uint16_t TTP229::GetKey(void) {
  byte i;
  uint16_t keycode = GetKeyCode();
  ST_KEY_MAP *irkeymap = em_ir_keymap;
  for (i = 0; i < KEY_MAX; i++) {
    //    Serial.println(irkeymap[i].keycode);
    if (irkeymap[i].keycode == keycode)
      return i;
  }
  return 0xff;
}



#endif



