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




#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "ohos_init.h"
#include "ohos_types.h"
#include <unistd.h>
#include "los_mux.h"
#include "hi_io.h"
#include "los_memory.h"
#include "utils_file.h"

#include <assert.h>
#include "py/compile.h"
#include "py/runtime.h"
#include "py/repl.h"
#include "py/gc.h"
#include "py/mperrno.h"
#include "shared/runtime/pyexec.h"
#include "shared/runtime/gchelper.h"
#include "hw_ctrl.h"
#include <unistd.h> 
#include "cmsis_os2.h" 
#include "iot_gpio.h" 
#include "iot_uart.h" 
#include "iot_i2c.h" 
#include "sal_reset.h"
#include "polygon_sys_cfg.h"
#include "pz_online.h"
#include "frame.h"
#include "mycrc16.h"
#include "sys_debug.h"
#include "hi_cpu.h"
#include "file_reader.h"
#include "los_hwi.h"
#include "pz_queue.h"
#include "py/ringbuf.h"






#define MP_TASK_STACK_SIZE 8192 

#define MD5_DIGEST_SIZE     16
#define IOT_UART_IDX_0      0



unsigned int osThreadGetStackStart(osThreadId_t thread_id)
{
	LosTaskCB *pstTaskCB = NULL;
	unsigned int uxReturn;
	if (OS_INT_ACTIVE || thread_id == NULL) {
    	return 0U;
	}
	pstTaskCB = (LosTaskCB *)thread_id;
	uxReturn = (UINT32)pstTaskCB->topOfStack;
	return uxReturn;
}


#if MICROPY_ENABLE_COMPILER
#if 1
void do_str(const char *src,int len, mp_parse_input_kind_t input_kind) {
    nlr_buf_t nlr;
    if (nlr_push(&nlr) == 0) {
		//PZ_SYS_DEBUG("do_str 1 \r\n");
        mp_lexer_t *lex = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, src, len, 0);
		//PZ_SYS_DEBUG("do_str 2 \r\n");
		qstr source_name = lex->source_name;
        mp_parse_tree_t parse_tree = mp_parse(lex, input_kind);
		//PZ_SYS_DEBUG("do_str 3 \r\n");
        mp_obj_t module_fun = mp_compile(&parse_tree, source_name, true);
		//PZ_SYS_DEBUG("do_str 4 \r\n");
		mp_call_function_0(module_fun);
		//PZ_SYS_DEBUG("do_str 5 \r\n");
        nlr_pop();
    } else {
        // uncaught exception
        //printf("uncaught exception");
        mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val);
    }
}

#endif
static void do_file(const char* filename)
{
    nlr_buf_t nlr = {0};
    
    if( nlr_push(&nlr) == 0 )
    {
        mp_lexer_t* lex = mp_lexer_new_from_file(filename);
        qstr source_name = lex->source_name;
        mp_parse_tree_t parse_tree = mp_parse(lex, MP_PARSE_FILE_INPUT);
        mp_obj_t module_fun = mp_compile(&parse_tree, source_name, false);
        mp_call_function_0(module_fun);
        m_free(lex);
        nlr_pop();
    }
    else
    {
        mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val);
    }
}

#endif

static char *stack_top;
#if MICROPY_ENABLE_GC
// static char heap[20480];
#define HEAP_SIZE (25*1024)
#define ENABLE_MALLOC_HEAP 1



#if ENABLE_MALLOC_HEAP

char *heap = NULL;
#else
static char heap[HEAP_SIZE];
#endif

#endif


int usr_uart_config(void) 
{
	
    int ret; 
    //初始化UART配置，115200，数据bit为8,停止位1，奇偶校验为NONE，流控为NONE 
    IotUartAttribute g_uart_cfg = {115200, 8, 1, IOT_UART_PARITY_NONE, 0, 0, 0}; 
    ret = IoTUartInit(IOT_UART_IDX_0, &g_uart_cfg); 
    if (ret != 0)  
    { 
        printf("uart init fail\r\n"); 
    }
	#if 0
	hi_uart_deinit(2);
	IoTGpioInit(11);//使用GPIO，都需要调用该接口 
	IoTGpioInit(12);//使用GPIO，都需要调用该接口 
	hi_io_set_func(11,2);
	hi_io_set_func(12,2);
	IotUartAttribute g_uart_cfg2 = {115200, 8, 1, IOT_UART_PARITY_NONE, 0, 0, 0}; 
    ret =IoTUartInit(2, &g_uart_cfg2); 
	if (ret != 0)  
    { 
        printf("uart2 init fail\r\n"); 
    }
	#endif
    return ret;
} 







static void UartDemo_Entry(void) 
{ 
   
    hi_uart_deinit(0);
    //IoTGpioInit(11);//使用GPIO，都需要调用该接口 
    //IoTGpioInit(12);//使用GPIO，都需要调用该接口 
    IoTGpioInit(3);//使用GPIO，都需要调用该接口 
    IoTGpioInit(4);//使用GPIO，都需要调用该接口 
    hi_io_set_func(3,1);
	hi_io_set_func(4,2);
    usr_uart_config(); 
} 



static inline void *get_sp()
{
    void *sp;
    __asm__ volatile ("mv %0, sp" : "=r"(sp));
    return sp;
}


int test = 0;
void micro_python(void *arg){
	
    stack_top = (char *)get_sp();
	#if MICROPY_PY_THREAD
    mp_thread_init((void*)osThreadGetStackStart(osThreadGetId()), MP_TASK_STACK_SIZE / sizeof(uintptr_t));
    #endif
    #if MICROPY_ENABLE_GC
#if ENABLE_MALLOC_HEAP
    heap = (char*)malloc(HEAP_SIZE*sizeof(char));
	if(heap == NULL){
		printf("malloc mp heap failed\r\n");
		return ;
	}
#endif
	mp_stack_set_top((void *)stack_top);
	#if MICROPY_STACK_CHECK
    mp_stack_set_limit(MP_TASK_STACK_SIZE - 1024);
	#endif
    gc_init(heap, heap + HEAP_SIZE);
    #endif
    //PZ_SYS_DEBUG("START MP\r\n");
    mp_init();
	
	mp_obj_list_init(mp_sys_path, 0);//这里初始化的是mp_state_ctx.vm.mp_sys_path_obj  
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR_));
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR__slash_lib));
    mp_obj_list_init(mp_sys_argv, 0);//这里初始化的是mp_state_ctx.vm.mp_sys_argv_obj  
	osDelay(1);
    #if MICROPY_ENABLE_COMPILER
    #if MICROPY_REPL_EVENT_DRIVEN
    //usleep(500000);
    
	
    pyexec_event_repl_init();
    for (;;) {
        int c = mp_hal_stdin_rx_chr();
        if (pyexec_event_repl_process_char(c)) {
            break;
        }
    }
	//PZ_SYS_DEBUG("START 12\r\n");
    #else
    //usleep(500000);
    
	//printf("2\r\n");
	do_file("main.py");
	//PZ_SYS_DEBUG("START 12\r\n");
    pyexec_friendly_repl();
    #endif
    // do_str("print('hello world!', list(x+1 for x in range(10)), end='eol\\n')", MP_PARSE_SINGLE_INPUT);
    // do_str("for i in range(10):\r\n  print(i)", MP_PARSE_FILE_INPUT);
    #else
	//PZ_SYS_DEBUG("START 13\r\n");
    pyexec_frozen_module("frozentest.py");
    #endif
    mp_deinit();
}





void micro_python_repl(void * arg){
    stack_top = (char *)get_sp();

	#if MICROPY_PY_THREAD
    mp_thread_init(osThreadGetStackStart(osThreadGetId()), MP_TASK_STACK_SIZE / sizeof(uintptr_t));
    #endif
	
    #if MICROPY_ENABLE_GC
#if ENABLE_MALLOC_HEAP
    heap = (char*)malloc(HEAP_SIZE*sizeof(char));
	if(heap == NULL){
		printf("malloc mp heap failed\r\n");
		return ;
	}
#endif
	mp_stack_set_top((void *)stack_top);
	#if MICROPY_STACK_CHECK
    mp_stack_set_limit(MP_TASK_STACK_SIZE - 1024);
	#endif
    gc_init(heap, heap + HEAP_SIZE);
    #endif
    //PZ_SYS_DEBUG("START MP\r\n");
    mp_init();
	mp_obj_list_init(mp_sys_path, 0);//这里初始化的是mp_state_ctx.vm.mp_sys_path_obj  
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR_));
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR__slash_lib));
    mp_obj_list_init(mp_sys_argv, 0);//这里初始化的是mp_state_ctx.vm.mp_sys_argv_obj  
	
    #if MICROPY_ENABLE_COMPILER
    #if MICROPY_REPL_EVENT_DRIVEN
    //usleep(500000);
    int fd = UtilsFileOpen("main.py", O_RDONLY_FS, 0);
    if(fd != -1){
        int size = 0;
        int flag = UtilsFileStat("main.py",&size);
        int len = size;
        char *buf = (char*)malloc(sizeof(char)*len);
        int readlen = UtilsFileRead(fd,buf,len);
        UtilsFileClose(fd);
        //do_str(buf,readlen, MP_PARSE_SINGLE_INPUT);
        do_str(buf,readlen, MP_PARSE_FILE_INPUT);
        free(buf);
    }
    pyexec_event_repl_init();
    for (;;) {
        int c = mp_hal_stdin_rx_chr();
        if (pyexec_event_repl_process_char(c)) {
            break;
        }
    }
    #else
    usleep(500000);
    pyexec_friendly_repl();
    #endif
    // do_str("print('hello world!', list(x+1 for x in range(10)), end='eol\\n')", MP_PARSE_SINGLE_INPUT);
    // do_str("for i in range(10):\r\n  print(i)", MP_PARSE_FILE_INPUT);
    #else
    pyexec_frozen_module("frozentest.py");
    #endif
    mp_deinit();
}

osThreadId_t *thread_list = NULL;
int thread_cnt = 0;
int thread_list_len = 20;
void launch_python(bool isRepl){
    osThreadAttr_t attr = {0};

    attr.name = "Python_Task";
    attr.attr_bits = 0U; 
    attr.cb_mem = NULL; 
    attr.cb_size = 0U; 
    attr.stack_mem = NULL; 
    attr.stack_size = MP_TASK_STACK_SIZE;//堆栈大小
    attr.priority = osPriorityNormal;//优先级 
    osThreadFunc_t mpy_launch_fun = NULL;
	if(isRepl){
		mpy_launch_fun = micro_python_repl;
	}else{
		mpy_launch_fun = micro_python;
	}
	osThreadId_t threadid = osThreadNew((osThreadFunc_t)mpy_launch_fun, NULL, &attr);
    if (threadid == NULL) {
        printf("[GpioExample] Falied to create GpioTask!\n");
    }else{
        thread_list[thread_cnt++] = threadid;
        if(thread_cnt == thread_list_len){
            osThreadId_t *new_thread_list = (osThreadId_t *)malloc(sizeof(osThreadId_t)*(thread_list_len + 20));
            for(int i=0;i<thread_list_len;i++){
                new_thread_list[i] = thread_list[i];
            }
            free(thread_list);
            thread_list = new_thread_list;
            thread_list_len = thread_list_len + 20;
        }
    }
}












FrameBufferStr frame_handle;
extern Msg_Queue_t g_uart_send_queue;
extern ringbuf_t stdin_ringbuf;


void free_all_mp_thread(){
	if(thread_cnt > 0){
		
        for(int i=0;i<thread_cnt;i++){
            osThreadTerminate(thread_list[i]);
            thread_list[i] = NULL;
        }
		
        thread_cnt = 0;
    }
}











int upload_file_fb = -1;
typedef struct{
	int fd;		
	uint16_t last_id;
	uint16_t pre_id;
	int8_t   success;
}upload_file_pro_t;

upload_file_pro_t up_file_ctrl={
								.fd=-1,
								.last_id = 0xffff,
								.pre_id  = 0X00,
								.success = 0,
}; 
int mp_uart_pro_send(uint8_t*send_buf,int len);

uint8_t upload_mp_script(uint8_t *buf, uint16_t len){
	if(buf[0]==0xa5 && buf[1] == 0x5a){
		if(buf[2]==0x04){
			//PZ_SYS_DEBUG("reererer %d %d\r\n",buf[3],buf[4]);
			/* 开始下载 */
			free_all_mp_thread();
			extern void exit_music_thread();
			exit_music_thread();
			
#if ENABLE_MALLOC_HEAP
            if(heap != NULL){
                free(heap);
				heap = NULL;
            }
#endif
			
			online_task_release();
			
			all_peripheral_deinit();
			if(buf[4] != HARDWARE_TYPE){
				/* 类型不正确 */
				//printf("FF%02X",HARDWARE_TYPE);
				/* 发送类型错误 */
				uint8_t buf[4];
				buf[0] = 'F';
				buf[1] = 'F';
				buf[2] = '0';
				buf[3] = '0'+HARDWARE_TYPE;
				mp_uart_pro_send(buf,4);
			}else{
				/* 打开文件 */
				if(up_file_ctrl.fd==-1){
					up_file_ctrl.fd = UtilsFileOpen("main.py", O_CREAT_FS | O_TRUNC_FS | O_WRONLY_FS, 0);
				}else{
					UtilsFileSeek(up_file_ctrl.fd,0,SEEK_SET_FS);
				}
				/* 回复>>> */
				up_file_ctrl.last_id = 0xffff;
				up_file_ctrl.pre_id  = 0X00;
				up_file_ctrl.success = 0;
				uint8_t buf[3];
				buf[0] = '>';
				buf[1] = '>';
				buf[2] = '>';
				mp_uart_pro_send(buf,3);
				/* 开始下载 */
			}
			return 5;
		}else{
			/* 获取数据长度 */
			int data_len = buf[2]<<8 | buf[3];
			if(len>=data_len){
				if(buf[4]==0X01){
					/* 文本内容 */				
					/* 获取内容长度 */
					uint16_t ctx_len = buf[7]<<8 | buf[8];
					/* 获取数据包id */
					uint16_t pre_id = buf[5]<<8 | buf[6];				
					uint16_t crc16 = buf[9+ctx_len]<<8 | buf[10+ctx_len];
					uint16_t local_crc16 = my_crc16(buf,data_len-2,1);
					/* 判断CRC胶验 */
					uint8_t send_data[8] = {0xa5,0x5a,0x00,0x08,0x01,0x00,0x00,0x00};
					send_data[5] = (pre_id>>8)&0xff;
					send_data[6] = pre_id&0xff;					
					//PZ_SYS_DEBUG("pre_id = %x,local_id = %d\r\n",pre_id,(uint16_t)(up_file_ctrl->last_id +1));
					
					if(crc16 == local_crc16){
						//PZ_SYS_DEBUG("crc_success\r\n");
						if(pre_id == (uint16_t)(up_file_ctrl.last_id +1)){
							/* id接收正确 */
							/* 将文本内容写到文本 */
							//PZ_SYS_DEBUG("id_success\r\n");
							if(up_file_ctrl.fd>=0){
								//PZ_SYS_DEBUG("id_success\r\n");
								int ret = UtilsFileWrite(up_file_ctrl.fd,(char*)&buf[9],ctx_len);
								if(ret < 0){
									/* 写入错误 */
									/* 返回写入错误数据包,总长度, */
									//PZ_SYS_DEBUG("write_error\r\n");
									send_data[7] = 0x01;
									
								}else{
									/* 写入成功 */
									/* 返回写入成功数据包 */
									up_file_ctrl.last_id = pre_id;
									//PZ_SYS_DEBUG("write_success\r\n");
									send_data[7] = 0x00;
								}
							}
						}else{
							/* id接收错误 */
							/* 返回写入错误数据包 */
							send_data[7] = 0x01;
						}
					}else{
						/* crc校验错误 */
						/* 返回写入错误数据包 */
						send_data[7] = 0x01;
					}
					//IoTUartWrite(0,send_data,0x08);
					mp_uart_pro_send(send_data,0x08);
				}else if(buf[4]==0X02){
					/* 接收完成 */
					//PZ_SYS_DEBUG("ggggggggg\r\n");
					uint8_t send_data[5] = {0xa5,0x5a,0x00,0x05,0x02};
					if(up_file_ctrl.fd>=0){
						UtilsFileClose(up_file_ctrl.fd);
						up_file_ctrl.fd = -1;
					}
					
					up_file_ctrl.success = 1;
					//IoTUartWrite(0,send_data,0x05);
					mp_uart_pro_send(send_data,0x05);
				}else if(buf[4]==0X03){
					/* 接收完成 */
					//PZ_SYS_DEBUG("aaaaaaaa\r\n");
					uint8_t send_data[5] = {0xa5,0x5a,0x00,0x05,0x03};
					if(up_file_ctrl.fd>=0){
						UtilsFileClose(up_file_ctrl.fd);
						up_file_ctrl.fd = -1;
					}
					//IoTUartWrite(0,send_data,0x05);
					mp_uart_pro_send(send_data,0x05);
				}else if(buf[4]==0X04){
					/* 接收完成 */
					//PZ_SYS_DEBUG("FIRMWARE_VERSION \r\n");
					uint8_t send_data[9] = {0xa5,0x5a,0x00,0x09,0x04};
					send_data[5]=((FIRMWARE_VERSION>>24)&0xff);
					send_data[6]=((FIRMWARE_VERSION>>16)&0xff);
					send_data[7]=((FIRMWARE_VERSION>>8)&0xff);
					send_data[8]=((FIRMWARE_VERSION)&0xff);
					//IoTUartWrite(0,send_data,0x09);
					mp_uart_pro_send(send_data,0x09);
				}
				return data_len;
			}
			
		}
		
	}
	return 0;
}


uint16_t server_recv_cb(uint8_t *buf, uint16_t len){
	static int8_t pro_data_flag=0;
	//Server_Potocal_t *potocal_ctrl = &g_ser_pro_ctrl;
	for(int i=0;i<len;i++){
		if(pro_data_flag==0){
			if(len-i==1 && buf[i]==0xA5){
				/* 只接收到0xA5 */
				//pro_data_flag =1;
				return i;
			}else if(len-i>=2&&buf[i]==0xA5&&buf[i+1]==0x5A){
				///PZ_SYS_DEBUG("Pro Start \r\n");
				pro_data_flag =1;
				return i;
			}
			/* 将数据添加到micropython */
			
			if (buf[i] == 0x03) {
				/* 接收到ctrl C */
				//PZ_SYS_DEBUG("Ctrl C \r\n");
				/* 释放所有python线程 */
				free_all_mp_thread();
				online_task_release();
#if ENABLE_MALLOC_HEAP
                if(heap != NULL){
                    free(heap);
                }
#endif
				/* 暂时注释 */
				//all_peripheral_deinit();
                mp_deinit();
				polygon_cfg_t*sys_cfg =  get_sys_cfg();
				sys_cfg->sys_mode = PZ_SCRIPT_MODE;
				update_sys_cfg(sys_cfg);
                launch_python(true);
				return i+1;
        	} else {
				
            	ringbuf_put(&stdin_ringbuf, buf[i]);
				return  i+1;
				
        	}
		}else {
			/* 这个是协议的数据 */
			/* 下载脚本 */
			uint16_t ret_len = upload_mp_script(buf+i,len-i);
			if(ret_len>0){
				pro_data_flag = 0;
				return ret_len+i;
			}
		}
	}
	
	if(pro_data_flag==0){
		return len;
	}else{
		pro_data_flag = 0;
        return 0;
    }
}



void mp_uart_mem_init(){
	Msg_Queue_Init(&g_uart_send_queue,1024);
	Init_Frame_Buffer(&frame_handle,1024,server_recv_cb);
	
}



int mp_uart_pro_send(uint8_t*send_buf,int len){	
	return Msg_Queue_Append_Lock(&g_uart_send_queue,send_buf,len);
}




uint8_t uart_send_buf[128]={0};
void mp_uart_send(){
	
	int send_len = Msg_Queue_Dequeue_Lock(&g_uart_send_queue,uart_send_buf,128);
	if(send_len>0){
		IoTUartWrite(0, uart_send_buf, send_len);
	}
}






void mp_uart_recv(){
	uint8_t read_buf[128];
	int len = IoTUartRead(0, read_buf, 128);
	Append_Frame_Buffer(&frame_handle,read_buf,len);	
}





void sys_thread(void *arg){
	mp_uart_mem_init();
	unsigned int size;
    UartDemo_Entry();
	//Sys_Debug_Init();
	int sys_mode = 0;
	polygon_cfg_t* cfg = get_sys_cfg();
	lunch_sys_cfg(cfg);
	thread_list = (osThreadId_t *)malloc(sizeof(osThreadId_t)*20);
	if(cfg->sys_mode == 0){
		launch_python(false);
	}else{
		/* 否则启动在线模式线程 */
		lunch_online();
	}
	while(1){
		/* 系统线程 */
		/* 接受数据处理协议 */
		/* 发送数据 */
		//
		//mp_uart_pro_send(send_buf,5);
		mp_uart_recv();
		mp_uart_send();
		if(up_file_ctrl.success == 1){
			osDelay(5);
			hi_reboot();
		}
		osDelay(1);
		//hi_watchdog_feed();
	}
	
	
}



void nfc_test(void);

int main_entry() {
	hi_watchdog_feed();
	hi_watchdog_disable();
	hi_cpu_set_clk(HI_CPU_CLK_160M);
	sys_thread(NULL);
    return 0;
}


#if MICROPY_ENABLE_GC
void gc_collect(void) {
    void *dummy = get_sp();
    gc_collect_start();
    //gc_collect_root(regs_ptr, ((uintptr_t)MP_STATE_THREAD(stack_top) - (uintptr_t)&regs) / sizeof(uintptr_t));
    gc_collect_root(&dummy, ((uintptr_t)MP_STATE_THREAD(stack_top) - (mp_uint_t)&dummy) / sizeof(mp_uint_t));
    #if MICROPY_PY_THREAD
   	mp_thread_gc_others();
    #endif
    gc_collect_end();
}
#endif



void nlr_jump_fail(void *val) {
    while (1) {
        ;
    }
}

void NORETURN __fatal_error(const char *msg) {
    while (1) {
        ;
    }
}

#ifndef NDEBUG
void MP_WEAK __assert_func(const char *file, int line, const char *func, const char *expr) {
    printf("Assertion '%s' failed, at file %s:%d\n", expr, file, line);
    __fatal_error("Assertion failed");
}
#endif


SYS_RUN(main_entry);
// APP_FEATURE_INIT(StartTrafficLightTask);
