#ifndef _POLYGON_ZONE_H
#define _POLYGON_ZONE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ohos_types.h"




#define   HW_TYPE_DASHIXIONG    0
#define   HW_TYPE_TIANQI        1
#define   HARDWARE_TYPE         HW_TYPE_DASHIXIONG//HW_TYPE_DASHIXIONG//HW_TYPE_DASHIXIONG

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

