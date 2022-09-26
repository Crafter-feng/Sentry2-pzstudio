/*
 * Copyright (C) 2022 Polygon Zone Open Source Organization .
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http:// www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 *
 * limitations under the License.
 */
 
 
 
 
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
#include "extdev_dht11_22.h"






#if BUILD_BOARD == DASHIXIONG_BOARD

#if 0

static int dht11_read_one_bit(extdev_dhtxx_obj_t *self)          
{  
	
    //gpio_direction_input(DHT11_PIN);  
    IotGpioValue val;
    IoTGpioSetDir(self->wire_pin.gpio_id,IOT_GPIO_DIR_IN);
    IoTGpioGetInputVal(self->wire_pin.gpio_id,&val);  
	return val;
}  





static void dht11_gpio_out(extdev_dhtxx_obj_t *self,int value)   
{  
	IoTGpioSetDir(self->wire_pin.gpio_id,IOT_GPIO_DIR_OUT);
	IoTGpioSetOutputVal(self->wire_pin.gpio_id,value);
}  




static unsigned char dht11_read_byte(extdev_dhtxx_obj_t *self)  
{   
    int i = 0;  
    int num;   
    unsigned char flag = 0;  
    unsigned char data = 0;  
  	IotGpioValue val;
	IoTGpioSetDir(self->wire_pin.gpio_id,IOT_GPIO_DIR_IN);
    for(num = 0; num < 8; num++)  
    {                
		i = 0;  
		/* 等待DHT11的引脚变为高电平 */
		IoTGpioGetInputVal(self->wire_pin.gpio_id,&val); 
		while(!val)  
		{  
			
			hi_udelay(10);  
			IoTGpioGetInputVal(self->wire_pin.gpio_id,&val); 
			i++;  
			if(i > 10)  
				break;  
		}  
		flag = 0x00;  
		hi_udelay(28);  
		IoTGpioGetInputVal(self->wire_pin.gpio_id,&val);
		if(val)  
		{  
			flag = 0x01;            
		}  
		i = 0;  
		IoTGpioGetInputVal(self->wire_pin.gpio_id,&val); 
		while(val)  
		{  
			IoTGpioGetInputVal(self->wire_pin.gpio_id,&val);
			hi_udelay(10);  
			i++;  
			if(i > 12)  
				break;  
		}  
		data <<= 1;  
		data |= flag;  
    }    
    return data;  
}

 


static void dht11_read_data(extdev_dhtxx_obj_t *self)  
{  
    int i = 0;  
	IotGpioValue val;
    dht11_gpio_out(self,0);  
    hi_udelay(30000);  
    dht11_gpio_out(self,1);  
    hi_udelay(20);  
    if(dht11_read_one_bit(self) == 0)  
    {   
    	IoTGpioGetInputVal(self->wire_pin.gpio_id,&val); 
        while(!val)  /* 等待IO口变为高电平 */
        {  
           hi_udelay(5);  
           i++;  
           if(i > 20)  
           {  
				break;  
           }  
        }  
        i = 0;  
		IoTGpioGetInputVal(self->wire_pin.gpio_id,&val);
        while(val)  /* 等待IO口变为低电平 */
        {  
           hi_udelay(5);  
           i++;  
           if(i > 20)  
           {  
              break;  
           }  
        }  
        for(i = 0; i < 5; i++) { /* 读取温湿度数据 */
        	self->dht11_data_buf[i] = dht11_read_byte(self);    
			printf("%d\r\n",self->dht11_data_buf[i]);
		}
 		
		/* 对读取到的数据进行校验 */
        self->dht11_data_buf[5] = self->dht11_data_buf[0]+self->dht11_data_buf[1]+self->dht11_data_buf[2]+self->dht11_data_buf[3];  
 
  		/* 判断读到的校验值和计算的校验值是否相同 */
        if(self->dht11_data_buf[4] == self->dht11_data_buf[5])	/* 相同则把标志值设为0xff */  
        {  
           self->check_flag = 0xff;   
        }  
        else if(self->dht11_data_buf[4] != self->dht11_data_buf[5]) /* 不相同则把标志值设为0 */
        {  
           self->check_flag = 0x00;  
                        
        }                     
    }  
}
#endif




void DHT11_IO_OUT(extdev_dhtxx_obj_t *self)
{
    //设置GPIO_11为输出模式
    IoTGpioSetDir(self->wire_pin.gpio_id, IOT_GPIO_DIR_OUT);
}
//初始化DHT11的IO口 DQ 同时检测DHT11的存在
//返回1:不存在
//返回0:存在    	 
//复位DHT11
void DHT11_Rst(extdev_dhtxx_obj_t *self)	   
{                
	DHT11_IO_OUT(self); 	//SET OUTPUT
    //DHT11_DQ_OUT_Low; 	//拉低DQ
    IoTGpioSetOutputVal(self->wire_pin.gpio_id,0);
    hi_udelay(20000);//拉低至少18ms
    IoTGpioSetOutputVal(self->wire_pin.gpio_id,1);
    //DHT11_DQ_OUT_High; 	//DQ=1 
	hi_udelay(35);     	//主机拉高20~40us
}



uint8_t GPIOGETINPUT(extdev_dhtxx_obj_t *self)
{
	IotGpioValue val;
    IoTGpioGetInputVal(self->wire_pin.gpio_id,&val);
	
    return val;
}

/****************************************
设置端口为输入
*****************************************/
void DHT11_IO_IN(extdev_dhtxx_obj_t *self)
{	
	IoTGpioSetDir(self->wire_pin.gpio_id, IOT_GPIO_DIR_IN);
    hi_io_set_pull(self->wire_pin.gpio_id, HI_IO_PULL_NONE);//配置为浮空输入
}

//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在
uint8_t DHT11_Check(extdev_dhtxx_obj_t *self) 	   
{   
	uint8_t retry=0;
	DHT11_IO_IN(self);//SET INPUT	 
    while (GPIOGETINPUT(self)&&retry<100)//DHT11会拉低40~80us
	{
		retry++;
		hi_udelay(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while ((!GPIOGETINPUT(self))&&retry<100)//DHT11拉低后会再次拉高40~80us
	{
		retry++;
		hi_udelay(1);
	};
	if(retry>=100)return 1;	   
	return 0;
}


//从DHT11读取一个位
//返回值：1/0
uint8_t DHT11_Read_Bit(extdev_dhtxx_obj_t *self) 			 
{
 	uint8_t retry=0;
	while(GPIOGETINPUT(self)&&retry<100){//等待变为低电平
	    retry++;
	    hi_udelay(1);
	}
    retry=0;
    while((!GPIOGETINPUT(self))&&retry<100){//等待变高电平
        retry++;
        hi_udelay(1);
    }
    hi_udelay(40);//等待40us	//用于判断高低电平，即数据1或0
    if(GPIOGETINPUT(self))return 1; else return 0;
}
//从DHT11读取一个字节
//返回值：读到的数据
uint8_t DHT11_Read_Byte(extdev_dhtxx_obj_t *self)    
{        
    uint8_t i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit(self);
    }						    
    return dat;
}



//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
uint8_t DHT11_Read_Data(extdev_dhtxx_obj_t *self,uint8_t *temp,uint8_t *humi)    
{        
 	uint8_t buf[5]={ 0 };
	uint8_t i;
	while((hi_get_us()-self->delay_time)<300000){
		usleep(1000);
	}
	self->delay_time = hi_get_us();
	DHT11_Rst(self);
	if(DHT11_Check(self)==0)
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=DHT11_Read_Byte(self);
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])//数据校验
		{
			*humi=buf[0];
			*temp=buf[2];
		}
	}else return 1;
	return 0;	    
}


MP_STATIC int extdev_dhtxx_obj_init_helper(extdev_dhtxx_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {

	int dht_gpio = mp_obj_get_int(pos_args[0]);
	/* scl是关键字参数 */
	s_pin parse_pin = parse_single_pin(dht_gpio);
	//printf("dht_gpio = %d\r\n",dht_gpio);
	if(parse_pin.gpio_aux.gpio_id != HI_GPIO_IDX_MAX){
		self->wire_pin = parse_pin.gpio_aux;
	}else{
		mp_raise_ValueError(MP_ERROR_TEXT("invalid pin"));
	}
	IoTGpioInit(self->wire_pin.gpio_id);
	/* 初始化gpio口 */
	hi_io_set_func(self->wire_pin.gpio_id,self->wire_pin.func);
	IoTGpioSetDir(self->wire_pin.gpio_id,HI_GPIO_DIR_OUT);
	IoTGpioSetOutputVal(self->wire_pin.gpio_id,1);
	DHT11_Rst(self);  //复位DHT11
	return 0;
}


MP_STATIC mp_obj_t extdev_dhtxx_obj_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
	extdev_dhtxx_obj_t *self = args[0];
	extdev_dhtxx_obj_init_helper(self, n_args - 1, args + 1, kw_args);
	return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(extdev_dhtxx_obj_init_obj, 3, extdev_dhtxx_obj_init);



MP_STATIC mp_obj_t extdev_dhtxx_get_temp(size_t n_args, const mp_obj_t *args) {
	extdev_dhtxx_obj_t *self = args[0];
	uint8_t temperature;
	uint8_t humidity;
	//LOS_TaskLock();
	
	//LOS_TaskUnlock();
	
	if(DHT11_Read_Data(self,&temperature,&humidity)==0)  
	{  
		/* 将读取的温湿度数据拷贝到用户空间 */
		return MP_OBJ_NEW_SMALL_INT(temperature);
	}  
	else 
	{
	 	return MP_OBJ_NEW_SMALL_INT(-1);
	}
	
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(extdev_dhtxx_get_temp_obj, 1, 1, extdev_dhtxx_get_temp);



MP_STATIC mp_obj_t extdev_dhtxx_get_humi(size_t n_args, const mp_obj_t *args) {
	extdev_dhtxx_obj_t *self = args[0];
	uint8_t temperature;
	uint8_t humidity;
	//LOS_TaskLock();
	
	//LOS_TaskUnlock();
	
	if(DHT11_Read_Data(self,&temperature,&humidity)==0)  
	{  
		/* 将读取的温湿度数据拷贝到用户空间 */
		return MP_OBJ_NEW_SMALL_INT(humidity);
	}  
	else 
	{
	 	return MP_OBJ_NEW_SMALL_INT(-1);
	}
	
}



MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(extdev_dhtxx_get_humi_obj, 1, 1, extdev_dhtxx_get_humi);

MP_STATIC void extdev_dhtxx_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    extdev_dhtxx_obj_t *self = self_in;
    mp_printf(print, "dht11 device driver");
}




mp_obj_t extdev_dhtxx_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 1, 1, true);
	extdev_dhtxx_obj_t *self = m_new_obj(extdev_dhtxx_obj_t);
	memset(self,0,sizeof(extdev_dhtxx_obj_t));
	self->wire_pin.gpio_id = HI_GPIO_IDX_MAX;
	self->base.type = type;
    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    int ret = extdev_dhtxx_obj_init_helper(self, n_args , args , &kw_args);
	if(ret==0){
    	return MP_OBJ_FROM_PTR(self);
	}else{
		return mp_const_none;
	}
}



MP_STATIC const mp_rom_map_elem_t extdev_dhtxx_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&extdev_dhtxx_obj_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_temp), MP_ROM_PTR(&extdev_dhtxx_get_temp_obj) },
    { MP_ROM_QSTR(MP_QSTR_humi), MP_ROM_PTR(&extdev_dhtxx_get_humi_obj) },
};



MP_STATIC MP_DEFINE_CONST_DICT(extdev_dhtxx_locals_dict, extdev_dhtxx_locals_dict_table);


const mp_obj_type_t extdev_DHTxx_type = {
    { &mp_type_type },
    .name = MP_QSTR_Dhtxx,
    .print = extdev_dhtxx_print,
    .make_new = extdev_dhtxx_make_new,
    .locals_dict = (mp_obj_dict_t *)&extdev_dhtxx_locals_dict,
};

#endif




