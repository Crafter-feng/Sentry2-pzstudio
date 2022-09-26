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




#ifndef __HAL_CTRL_H
#define __HAL_CTRL_H

#include "iot_gpio.h"
#include "iot_i2c.h" 
#include "hi_spi.h"
#include "iot_pwm.h"
#include "hi_io.h"
#include "hi_adc.h"
#include "hi_pwm.h"
#include "hi_i2c.h"
#include "hi_gpio.h"
#include "hi_uart.h"


void all_peripheral_deinit();


#endif

