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



#ifndef  EXTDEV_TTP229_H
#define  EXTDEV_TTP229_H



#include "hi_io.h"
#include "hi_gpio.h"



typedef struct _extdev_ttp229_obj_t {
    mp_obj_base_t base;
	uint8_t _key8, _keys8, _key16;
	uint16_t _keys16;
	gpio_func  scl_pin;
	gpio_func  sdo_pin;
} extdev_ttp229_obj_t;


uint8_t ReadKey8(extdev_ttp229_obj_t *self);
uint8_t GetKey8(extdev_ttp229_obj_t *self);
uint8_t ReadKeys8(extdev_ttp229_obj_t *self);
uint8_t GetKeys8(extdev_ttp229_obj_t *self);
uint8_t ReadKey16(extdev_ttp229_obj_t *self);
uint8_t GetKey16(extdev_ttp229_obj_t *self);
uint16_t ReadKeys16(extdev_ttp229_obj_t *self);
uint16_t GetKeys16(extdev_ttp229_obj_t *self);
void Key8(extdev_ttp229_obj_t *self);
void Keys8(extdev_ttp229_obj_t *self);
void Key16(extdev_ttp229_obj_t *self);
void Keys16(extdev_ttp229_obj_t *self);
bool GetBit(extdev_ttp229_obj_t *self);
bool IsTouch(extdev_ttp229_obj_t *self);
void WaitForTouch(extdev_ttp229_obj_t *self);






#endif


