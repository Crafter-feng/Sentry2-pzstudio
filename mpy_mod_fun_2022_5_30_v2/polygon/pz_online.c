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





#include "pz_online.h"
#include "cmsis_os2.h" 


static osThreadId_t online_threadid = NULL;


void pz_online_task(){
	
	while(1){
		//printf("pz_online_task\r\n");
		osDelay(200);
	}
}




int lunch_online(void){
	osThreadAttr_t attr = {0};
    attr.name = "Python_Task";
    attr.attr_bits = 0U; 
    attr.cb_mem = NULL; 
    attr.cb_size = 0U; 
    attr.stack_mem = NULL; 
    attr.stack_size = 8192;//堆栈大小
    attr.priority = osPriorityNormal;//优先级 
    if(online_threadid == NULL){
		online_threadid = osThreadNew((osThreadFunc_t)pz_online_task, NULL, &attr);
    }
	if(online_threadid == NULL){
		printf("lunch online task failed\r\n");
		return -1;
	}else{
		printf("lunch online task success\r\n");
	}

	return 0;
}





void online_task_release(){
	if(online_threadid!=NULL){
		osThreadTerminate(online_threadid);
		printf("del online task success\r\n");
		online_threadid = NULL;
	}
	
}




