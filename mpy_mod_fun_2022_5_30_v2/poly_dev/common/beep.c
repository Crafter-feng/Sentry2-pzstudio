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


#include "beep.h"


#define CLK_40M 40000000
#define DUTY_MIN 0
#define DUTY_MAX 100
#define SHORT_MAX 0xFFFF





int beep_init(void)
{
    IoTGpioInit(HW_BEEP_PIN);
    hi_io_set_func(HW_BEEP_PIN,HW_BEEP_FUN);
    IoTGpioSetDir(HW_BEEP_PIN, IOT_GPIO_DIR_OUT);
    hi_pwm_set_clock(PWM_CLK_XTAL);
	hi_pwm_init(HW_BEEP_PWM);
	beep_off();
    return 0;
}





void beep_deinit(void){
	beep_off();
	hi_pwm_deinit(HW_BEEP_PWM);
	hi_io_set_func(HW_BEEP_PIN,0);
	IoTGpioDeinit(HW_BEEP_PIN);
}




int beep_on(void)
{
	beep_set(1000,50);
    return 0;
}




int beep_off(void)
{
    hi_pwm_stop(HW_BEEP_PWM);
    return 0;
}


int beep_set(unsigned     int freq, unsigned short volume)
{
	unsigned short hiDuty;
    unsigned short hiFreq;
	if(volume==0){
		hi_pwm_stop(HW_BEEP_PWM);
	}
	 if ((freq == 0) || (volume >= DUTY_MAX) || (volume == DUTY_MIN)) {
        return -1;
    }
    if ((CLK_40M / freq) > SHORT_MAX) {
        return -1;
    }
	hiFreq = (unsigned short)(CLK_40M / freq);
    hiDuty = (volume * hiFreq) / DUTY_MAX;
	hi_pwm_start(HW_BEEP_PWM, hiDuty, hiFreq);
    return 0;
}





