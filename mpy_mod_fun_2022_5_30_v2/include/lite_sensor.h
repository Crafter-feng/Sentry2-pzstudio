/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef __LITE_SENSOR_H__
#define __LITE_SENSOR_H__
#include "parse_pin.h"


/* track module */
typedef enum {
    BLACK = 0,
    WHITE,
    UNKNOWN,
} trace_state;


// function statements
/* gpio series */
hi_void set_led_val(hi_u8 pin_num, hi_u8 set_val);
hi_s8 get_touch_val(hi_u8 pin_num);
hi_s8 tqs1_touch_get_val(hi_void);
hi_s8 get_key_val(hi_u8 pin_num);
hi_s8 tqs1_key_get_val(hi_u8 key_num);
trace_state get_trace_val(hi_u8 pin_num, hi_u8 dir);

/* adc series */
hi_u16 get_light_intensity(hi_u8 pin_num);
hi_u16 tqs1_light_get_intensity(hi_void);
hi_u16 get_voice_intensity(hi_u8 pin_num);
hi_u16 tqs1_voice_get_intensity(hi_void);
hi_u16 get_soil_moisture_intensity(hi_u8 pin_num);
hi_u16 get_flame_intensity(hi_u8 pin_num);

/* pwm likely series */
hi_void buzzer_music(hi_u8 pin_num, hi_u8 type);
hi_void buzzer_beat(hi_u8 pin_num, hi_u8 tune, hi_u16 duration);
hi_void tqs1_buzzer_music(hi_u8 type);
hi_void tqs1_buzzer_beat(hi_u8 tune, hi_u16 duration);
hi_void fan(hi_u8 pin_num, hi_u16 speed);
hi_void motor(hi_u8 pin_num, hi_s16 speed);
hi_void servo(hi_u8 pin_num, hi_u8 angle);

/* others */
hi_u16 ultrasonic(hi_u8 pin_num);

/* pin control */
hi_void set_digital_val(hi_u8 pin_num, hi_u8 set_val);
hi_void set_double_digital_val(hi_u8 pin_num, hi_u8 pin_dir, hi_u8 set_val);
hi_s8 get_digital_val(hi_u8 pin_num);
hi_s8 get_double_digital_val(hi_u8 pin_num, hi_u8 pin_dir);
hi_u16 get_analog_val(hi_u8 pin_num);
hi_void set_analog_val(hi_u8 pin_num, hi_u16 duty);

/* timer */
hi_void timer_reset(hi_void);
hi_u32 timer_get_time(hi_void);
#endif