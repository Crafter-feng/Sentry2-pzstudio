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






#ifndef _POLYGON_ZONE_H
#define _POLYGON_ZONE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ohos_types.h"




#define   HW_TYPE_DASHIXIONG    0
#define   HW_TYPE_TIANQI        1
#define   HARDWARE_TYPE         HW_TYPE_DASHIXIONG//HW_TYPE_DASHIXIONG//HW_TYPE_DASHIXIONG
#define   FIRMWARE_VERSION      0X00010011



#define   PZ_SCRIPT_MODE        0
#define   PZ_ONLINE_MODE        1
#define   PZ_DEFAULT_MODE       PZ_SCRIPT_MODE   




typedef struct{
	/* 模式 */
	char sys_mode;
	/* 型号 */
	char sys_type;
}polygon_cfg_t;



polygon_cfg_t* get_sys_cfg(void);
int update_sys_cfg(polygon_cfg_t *cfg);
int lunch_sys_cfg(polygon_cfg_t *cfg);
unsigned int pz_random();
unsigned int ploygon_get_time();


#endif

