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




#ifndef AHT20_H
#define AHT20_H

#include <hi_types_base.h>
#include <hi_i2c.h>
#include <hi_early_debug.h>
#include <hi_stdlib.h>

int AHT20_GetMeasureResult(float* temp, float* humi);

hi_void aht2x_prepare();

int tqs1_aht2x_init();
float tqs1_aht2x_get_value(hi_u8 type);
#endif  // AHT20_H