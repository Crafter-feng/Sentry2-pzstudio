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





#include "polygon_sys_cfg.h"
#include "utils_file.h"
#include "cmsis_os2.h" 




static polygon_cfg_t sys_cfg;



//找出temp在target的位置
int find_index(char *target,char temp){
    int i= 0;
    if(target ==NULL){
        //printf("搜索词为空...");
        //exit(-1); //异常退出
        return -1;
    }
    for(i = strlen(target) -1;i>=0;i--){
        if(target[i] == temp){
            return i;
        }
    }
    return -1;  //未找到字符匹配位置

}



//sunday算法
int sunday_search(char *source,char *target){

    int i= 0,j = 0,srclen = strlen(source),tarlen=strlen(target);
    int temp  =0,index = -1;
    if(source ==NULL || target ==NULL){
        //printf("请初始化...\n");
        return -1;
    }

    while(i<srclen){  //循环条件
        if(source[i] == target[j]){
            if(j==tarlen-1){
				//printf("i=%d, j=%d\r\n",i,j);
				return i-j+1;
            }
            i++;j++;
        }else{
            temp = tarlen - j + i;
            index = find_index(target,source[temp]);
            if(index==-1){
                i = temp+1;
                j = 0;
            }else{
                i = temp-index;
                j = 0;
            }
        }
    }
    return -1;
}








int lunch_sys_cfg(polygon_cfg_t *cfg){
	/* 加载 */
	int fd = UtilsFileOpen("sys.cfg",O_RDONLY_FS,0);
	if(fd<0){
		sys_cfg.sys_mode = PZ_DEFAULT_MODE;
		sys_cfg.sys_type = HARDWARE_TYPE;
		update_sys_cfg(&sys_cfg);
	}else{
		/* 读取文件 */
		unsigned int size;
		sys_cfg.sys_mode = PZ_DEFAULT_MODE;
		sys_cfg.sys_type = HARDWARE_TYPE;
		//printf("file is exist\r\n");
		UtilsFileStat("sys.cfg",&size);
		//printf("size = %d\r\n",size);
		char* buffer = malloc(size*sizeof(char));
		if(buffer!=NULL){
			int len = UtilsFileRead(fd,buffer,size);
			int index = 0;
			//printf("len = %d, data<%s>\r\n",len,buffer);
			if(len>=0){
				/* 第二次上电加载数据 */
				index = sunday_search(buffer,"sys_mode:");
				int tar_len = strlen("sys_mode:");
				//printf("index = %d\r\n",index);
				if(index+tar_len-1 < len){
					//printf("sys_mode:%c\r\n",buffer[index+tar_len-1]);
					sys_cfg.sys_mode = buffer[index+tar_len-1]-'0';
					
				}
				/*  */
				index = sunday_search(buffer,"sys_type:");
				tar_len = strlen("sys_type:");
				//printf("index = %d\r\n",index);
				if(index+tar_len-1 < len){
					//printf("sys_type:%c\r\n",buffer[index+tar_len-1]);
					sys_cfg.sys_type = buffer[index+tar_len-1]-'0';
				}
			}else{
				
			}
			free(buffer);
			buffer = NULL;
		}else{
		}
		UtilsFileClose(fd);
	}
	if(cfg!=NULL){
		memcpy(cfg,&sys_cfg,sizeof(polygon_cfg_t));
		return 0;
	}else{
		return -1;
	}
}






int update_sys_cfg(polygon_cfg_t *cfg){
	/* 删除文件系统 */
	if(cfg != NULL){
		UtilsFileDelete("sys.cfg");
		int fd = UtilsFileOpen("sys.cfg",O_CREAT_FS|O_TRUNC_FS|O_RDWR_FS,0);
		if(fd>0){
			/* 文件打开失败 */
			char* buffer = malloc(32*sizeof(char));
			if(buffer!=NULL){
				/* 系统默认模式 */
				memset(buffer, 0,32);
				sprintf(buffer,"<sys_mode:%d>",cfg->sys_mode);
				UtilsFileWrite(fd,buffer,strlen(buffer));

				/* 系统默认类型 */
				memset(buffer, 0,32);
				sprintf(buffer,"<sys_type:%d>",cfg->sys_type);
				UtilsFileWrite(fd,buffer,strlen(buffer));
				free(buffer);
			}
			UtilsFileClose(fd);
			return 0;
		}else{
			return -2;
		}
	}else{
		return -1;
	}
}









unsigned int pz_random()
{
    unsigned int rnd;
    srand(hi_get_us()*rand()); /* seed是一个种子数值，可以使用当前时间戳等 */
    rnd=rand();
    return rnd;
}




polygon_cfg_t* get_sys_cfg(void){
	return &sys_cfg;
}



unsigned int ploygon_get_time(){
	uint64_t tickCount = LOS_TickCountGet();
    return LOS_Tick2MS(tickCount);
	
}




