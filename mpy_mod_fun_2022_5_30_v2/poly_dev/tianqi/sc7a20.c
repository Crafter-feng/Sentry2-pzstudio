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



#include "sc7a20.h"
#include "hal_pz_i2c.h"
#if BUILD_BOARD == TQ_BOARD

hi_u8 SC7A20_Msg = 8;
hi_u8 SC7A20_REG[10] = {0x2f,0x04,0x88,0x05,0x08,0x02,0x05,0x01,0x15,0x80};
hi_u8 Acc_Data[3];
//SC7A20_I2C_WADDR
//SC7A20_I2C_RADDR
static hi_u32 SC7A20_Read(hi_u8* buffer, hi_u32 buffLen)
{
    
    return hal_pz_i2c_read(1,SC7A20_I2C_ADDR,buffer,buffLen);
}

static hi_u32 SC7A20_Write(hi_u8* buffer, hi_u32 buffLen)
{
	
    return hal_pz_i2c_write(1,SC7A20_I2C_ADDR, buffer,buffLen);
}

hi_u32 SC7A20_readfrom(hi_u8 reg_addr, hi_u8 *reg_val)
{
    hi_u8 send_buf[1] = {reg_addr};
    hi_u8 recv_buf[1] = {0};
    hi_u32 status;
    //先写
    status = SC7A20_Write(send_buf, 1);
    if(status != HI_ERR_SUCCESS){
        printf("SC7A20_readfrom 0x%x fail\r\n", reg_addr);
        return HI_ERR_FAILURE;
    }
    //后读
    status = SC7A20_Read(recv_buf, 1);
    if(status != HI_ERR_SUCCESS){
        printf("Error: I2C read status = 0x%x!\r\n", status);
        return HI_ERR_FAILURE;
    }
    *reg_val = recv_buf[0];
    return HI_ERR_SUCCESS;
}

hi_u32 SC7A20_writeto(hi_u8 reg_addr, hi_u8 reg_val)
{
    hi_u8 send_buf[2] = {reg_addr, reg_val};
    hi_u32 status;

    status = SC7A20_Write(send_buf, 2);
    if(status != HI_ERR_SUCCESS){
        printf("Error: I2C writeto 0x%x fail, status = 0x%x!\r\n", reg_addr, status);
        return HI_ERR_FAILURE;
    }
    return HI_ERR_SUCCESS;
}


hi_u32 SC7A20_readblock_from(hi_u8 reg_addr, hi_u8* recv_buf, hi_u32 recv_len)
{
    hi_u8 send_buf[1] = {reg_addr};
    hi_u32 status;

    //先写
    status = SC7A20_Write(send_buf, 1);
    if(status != HI_ERR_SUCCESS){
        printf("APDS9960_readblock_from 0x%x fail, status = 0x%x!\r\n", reg_addr, status);
        return 0;
    }

    //后读
    status = SC7A20_Read(recv_buf, recv_len);
    if(status != HI_ERR_SUCCESS){
        printf("Error: I2C read status = 0x%x!\r\n", status);
        return 0;
    }

    return strlen(recv_buf);
}


//hi_u8
hi_u8 SC7A20_Init()
{
	
	hi_u8  temp1;
	hal_pz_i2c_init(1,400000);
	SC7A20_readfrom(0x0F,&temp1);   
	printf("Chip_ID = %x\r\n", temp1);
	
	SC7A20_writeto(0x20,SC7A20_REG[0]);  //odr 10Hz
	SC7A20_writeto(0x21,SC7A20_REG[1]);  //fds -->开启高通滤波器(滤掉地球G)(一定要开启，否则阈值要超过1G，而且动作也要超过1G)
	SC7A20_writeto(0x23,SC7A20_REG[2]);  //range bdu  0x20--0xA8
	
    return 0;
}


hi_s32 SC7A20_Get_ACCD(hi_u8 accd_lsb,hi_u8 accd_msb)
{
	hi_u8 accd_l,accd_m = 0;
	hi_u32 temp;
	hi_s32 accd;
  hi_s16 accd_value; 
	SC7A20_readfrom(accd_lsb,&accd_l);
	SC7A20_readfrom(accd_msb,&accd_m);
  accd_value = (accd_l + (accd_m<<8))>>6;
  accd_value &= 0x03ff;
  if(accd_value >> 9)//负数
  {
    accd_value &= 0x01ff;
    accd_value = ~accd_value;
    accd_value += 1;
    accd_value &= 0x01ff;
    accd_value = - accd_value;
  }
  /*
	temp &= 0x0000;
	temp |= accd_m;
	temp <<= 8;
	temp &= 0xff00;
	temp |= accd_l;	
	if(temp&0x8000)
	{
		temp >>= 4;
		temp |= 0xf000;
	}
	else
	{
		temp >>= 4;
		temp &= 0x0fff;
	}
	accd = temp*1;
  */
  accd = accd_value * 16;
	return accd;
}

hi_s32 * SC7A20_GetInfo()
{
	//hi_s32 x,y,z = 0;
  	static hi_s32 a[3] = {0};//x,y,z = 0;
	hi_u8 i = 16;
	for(i=8;i>0;i--)
	{
		a[0] += SC7A20_Get_ACCD(0x28,0x29);
		a[1] += SC7A20_Get_ACCD(0x2A,0x2B);
		a[2] += SC7A20_Get_ACCD(0x2C,0x2D);
	}
	a[0] /= 8;
	a[1] /= 8;
	a[2] /= 8;	
	
  	//a[0] /= 1000;
	//a[1] /= 1000;
	//a[2] /= 1000;	
  return a;
}

hi_s32 get_x(hi_void){
        hi_s32 *a = NULL;
        a = SC7A20_GetInfo();
        return a[0];
}
hi_s32 get_y(hi_void){
        hi_s32 *a = NULL;
        a = SC7A20_GetInfo();
        return a[1];
}
hi_s32 get_z(hi_void){
        hi_s32 *a = NULL;
        a = SC7A20_GetInfo();
        return a[2];
}
hi_s32 motion(hi_void){
        hi_s32 *a = NULL;
        a = SC7A20_GetInfo();
        //shaked
        if(a[0] > 5000 || a[1] > 5000 || a[2] > 5000)
          return 0; 
        //face up
        else if (a[0]>50 && a[0]<300 && a[1]>-200 && a[1]<200 && a[2]>-5000 && a[2]<-3200)
          return 5;
        //face down
        else  if (a[0]>50 && a[0]<350 && a[1]>-370 && a[1]<350 && a[2]>3200 && a[2]<5000)
          return 6;
        //up
        else  if (a[0]>90 && a[0]<200 && a[1]>-3600 && a[1]<-1400 && a[2]>-4800 && a[2]<-3000)
          return 1;
        //down
        else  if (a[0]>200 && a[0]<500 && a[1]>1400 && a[1]<3600 && a[2]>-4800 && a[2]<-2900)
          return 2;
        //left
        else  if (a[0]>1500 && a[0]<3800 && a[1]>-500 && a[1]<500 && a[2]>-4500 && a[2]<-3200)
          return 3;
        //right
        else  if (a[0]>-3200 && a[0]<-1300 && a[1]>-500 && a[1]<500 && a[2]>-4300 && a[2]<-2900)
          return 4;
        else
          return 7;

}
#endif
