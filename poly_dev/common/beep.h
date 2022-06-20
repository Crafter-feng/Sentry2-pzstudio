/*
* Copyright (c) 2006-2018, RT-Thread Development Team
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date           Author       Notes
* 2018-10-17     flybreak      the first version
*/

#ifndef BEEP_H
#define BEEP_H


#include "ohos_types.h"
#include "ohos_init.h"
#include "iot_watchdog.h"
#include "iot_pwm.h"
#include "hi_io.h"
#include "hi_adc.h"
#include "hi_time.h"
#include <hi_task.h>
#include <hi_spi.h>
#include <hi_gpio.h>
#include <hi_pwm.h>
#include "iot_gpio.h" 
#include "polygon_sys_cfg.h"






#if HARDWARE_TYPE == HW_TYPE_DASHIXIONG
#define HW_BEEP_PIN     HI_IO_NAME_GPIO_5
#define HW_BEEP_FUN     HI_IO_FUNC_GPIO_5_PWM2_OUT
#define HW_BEEP_PWM     HI_PWM_PORT_PWM2


#elif HARDWARE_TYPE == HW_TYPE_TIANQI
#define HW_BEEP_PIN     HI_IO_NAME_GPIO_12
#define HW_BEEP_FUN     HI_IO_FUNC_GPIO_12_PWM3_OUT
#define HW_BEEP_PWM     HI_PWM_PORT_PWM3
#endif

   
int beep_init(void);                         //蜂鸣器初始化
void beep_deinit(void);
int beep_on(void);                           //蜂鸣器开
int beep_off(void);                          //蜂鸣器关
int beep_set(unsigned     int freq, unsigned short volume); //蜂鸣器设定

#endif
