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
#include "md5.h"
#include "sal_reset.h"
#include "polygon_sys_cfg.h"
#include "pz_online.h"
#include "frame.h"
#include "mycrc16.h"
#include "sys_debug.h"
#include "hi_cpu.h"
#include "file_reader.h"
#include "los_hwi.h"






#define MP_TASK_STACK_SIZE 8192 

#define MD5_DIGEST_SIZE     16
#define IOT_UART_IDX_2      0

unsigned char uartWriteBuff[] = "hello uart!";
unsigned char uartWriteBuff2[] = "recv uart!";
unsigned char uartReadBuff[512] = {0};



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
#if 0
void do_str(const char *src,int len, mp_parse_input_kind_t input_kind) {
    nlr_buf_t nlr;
    if (nlr_push(&nlr) == 0) {
		PZ_SYS_DEBUG("do_str 1 \r\n");
        mp_lexer_t *lex = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, src, len, 0);
		PZ_SYS_DEBUG("do_str 2 \r\n");
		qstr source_name = lex->source_name;
        mp_parse_tree_t parse_tree = mp_parse(lex, input_kind);
		PZ_SYS_DEBUG("do_str 3 \r\n");
        mp_obj_t module_fun = mp_compile(&parse_tree, source_name, true);
		PZ_SYS_DEBUG("do_str 4 \r\n");
		mp_call_function_0(module_fun);
		PZ_SYS_DEBUG("do_str 5 \r\n");
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
    ret = IoTUartInit(IOT_UART_IDX_2, &g_uart_cfg); 
    if (ret != 0)  
    { 
        printf("uart init fail\r\n"); 
    }
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
    PZ_SYS_DEBUG("START MP\r\n");
    mp_init();
	
	mp_obj_list_init(mp_sys_path, 0);//这里初始化的是mp_state_ctx.vm.mp_sys_path_obj  
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR_));
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR__slash_lib));
    mp_obj_list_init(mp_sys_argv, 0);//这里初始化的是mp_state_ctx.vm.mp_sys_argv_obj  
	
    #if MICROPY_ENABLE_COMPILER
    #if MICROPY_REPL_EVENT_DRIVEN
    //usleep(500000);
    #if 0
    int fd = UtilsFileOpen("main.py", O_RDONLY_FS, 0);
    if(fd != -1){
        int size = 0;
        int flag = UtilsFileStat("main.py",&size);
        int len = size;
        char *buf = (char*)malloc(sizeof(char)*len);
		LOS_MEM_STATUS mem_status ;
		/*
		LOS_MemInfoGet(OS_SYS_MEM_ADDR, &mem_status);
		printf("free_size = %x\r\n",mem_status.freeSize);
		printf("free_size = %x\r\n",mem_status.freeCount);
		*/
        int readlen = UtilsFileRead(fd,buf,len);
        UtilsFileClose(fd);
        do_str(buf,readlen, MP_PARSE_SINGLE_INPUT);
        free(buf);
    }
	#else
	//printf("1\r\n");
	do_file("main.py");
	#endif
	
    pyexec_event_repl_init();
    for (;;) {
        int c = mp_hal_stdin_rx_chr();
        if (pyexec_event_repl_process_char(c)) {
            break;
        }
    }
	PZ_SYS_DEBUG("START 12\r\n");
    #else
    //usleep(500000);
    #if 0
    int fd = UtilsFileOpen("main.py", O_RDONLY_FS, 0);
    if(fd != -1){
        int size = 0;
        int flag = UtilsFileStat("main.py",&size);
        if(size > 0){
            int len = size;
			PZ_SYS_DEBUG("aaaaa\r\n");
            char *buf = (char*)malloc(sizeof(char)*len);
			/*
			LOS_MEM_STATUS mem_status ;
			LOS_MemInfoGet(OS_SYS_MEM_ADDR, &mem_status);
			printf("free_size = %x\r\n",mem_status.freeSize);
			printf("free_size = %x\r\n",mem_status.freeCount);
			*/
            int readlen = UtilsFileRead(fd,buf,len);
			PZ_SYS_DEBUG("bbbbbb\r\n");
            //do_str(buf,readlen, MP_PARSE_FILE_INPUT);
            free(buf);
            UtilsFileClose(fd);
        }else{
            UtilsFileClose(fd);
        }
       
    }
	#else
	//printf("2\r\n");
	do_file("main.py");
	#endif
	PZ_SYS_DEBUG("START 12\r\n");
    pyexec_friendly_repl();
    #endif
    // do_str("print('hello world!', list(x+1 for x in range(10)), end='eol\\n')", MP_PARSE_SINGLE_INPUT);
    // do_str("for i in range(10):\r\n  print(i)", MP_PARSE_FILE_INPUT);
    #else
	PZ_SYS_DEBUG("START 13\r\n");
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
    PZ_SYS_DEBUG("START MP\r\n");
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










typedef struct{
	int fd;	
    int8_t loop_flag;
	uint16_t last_id;
	uint16_t pre_id;
	int8_t   success;
}upload_file_pro_t;

UINT32 uartMux;
// unsigned char uartReadBuff[4096] = {0};
unsigned char sharedUartReadBuff[512] = {0};
unsigned int write_bufIndex = 0;

unsigned char sharedUartWriteBuff[512] = {0};
unsigned int write_uartIndex = 0;
unsigned int writeLen = 0;
upload_file_pro_t *up_file_ctrl;





uint16_t up_file_protocal_cb(uint8_t *buf, uint16_t len){
	#define UP_FILE_PRO_HEAD_LEN 
	if(up_file_ctrl!=NULL){
		if(buf[0]==0xa5 && buf[1] == 0x5a){
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
						if(pre_id == (uint16_t)(up_file_ctrl->last_id +1)){
							/* id接收正确 */
							/* 将文本内容写到文本 */
							//PZ_SYS_DEBUG("id_success\r\n");
							if(up_file_ctrl->fd>=0){
								//PZ_SYS_DEBUG("id_success\r\n");
								int ret = UtilsFileWrite(up_file_ctrl->fd,(char*)&buf[9],ctx_len);
								if(ret < 0){
									/* 写入错误 */
									/* 返回写入错误数据包,总长度, */
									//PZ_SYS_DEBUG("write_error\r\n");
									send_data[7] = 0x01;
									
								}else{
									/* 写入成功 */
									/* 返回写入成功数据包 */
									up_file_ctrl->last_id = pre_id;
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
					IoTUartWrite(0,send_data,0x08);
				}else if(buf[4]==0X02){
					/* 接收完成 */
					uint8_t send_data[5] = {0xa5,0x5a,0x00,0x04,0x02};
					if(up_file_ctrl->fd>=0){
						UtilsFileClose(up_file_ctrl->fd);
						up_file_ctrl->fd = -1;
					}
					up_file_ctrl->loop_flag = 0;
					up_file_ctrl->success = 1;
					IoTUartWrite(0,send_data,0x05);
				}else if(buf[4]==0X03){
					/* 接收完成 */
					uint8_t send_data[5] = {0xa5,0x5a,0x00,0x04,0x03};
					if(up_file_ctrl->fd>=0){
						UtilsFileClose(up_file_ctrl->fd);
						up_file_ctrl->fd = -1;
					}
					up_file_ctrl->loop_flag = 0;
					IoTUartWrite(0,send_data,0x05);
				}
				return data_len;
			}
		}
	}
	return 0;
}




/* 系统线程 */
void sys_thread(){
	uint32_t timer_out_cnt;
    if (uartMux == NULL){
        LOS_MuxCreate(&uartMux);
    }
    unsigned int len = 0; 
    unsigned char uartReadBuff[128] = {0};
    unsigned char c = 0;
	char sys_mode = -1;
	char board_type = -1;
	uint32_t timer_delay = 0;
	
    while(true){
		/*
		if((test_get_time() - timer_delay)>=1000){
			//gc_collect();
			gc_dump_info();
			timer_delay = test_get_time();
		}
		*/
        LOS_MuxPend(uartMux, LOS_WAIT_FOREVER);
        len = IoTUartRead(0, uartReadBuff, 1);
        if(len > 0){
            if(len >= 1 && uartReadBuff[0] == 4){
                if(thread_cnt > 0){ 
                    for(int i=0;i<thread_cnt;i++){
                        osThreadTerminate(thread_list[i]);
                        thread_list[i] = NULL;
                    }
                    thread_cnt = 0;
                }
				extern void exit_music_thread();
				exit_music_thread();
				
#if 0
				extern void stop_play_music();
				stop_play_music();
#endif
#if ENABLE_MALLOC_HEAP
                if(heap != NULL){
                    free(heap);
					heap = NULL;
                }
#endif
				online_task_release();
				all_peripheral_deinit();
				timer_out_cnt = 0;
				while((len = IoTUartRead(0, uartReadBuff, 1))<=0){
					timer_out_cnt++;
					if(timer_out_cnt>1000000){
						break;
					}
					osDelay(1);
				}
				if(len>0){
					sys_mode = uartReadBuff[0];
				}
				timer_out_cnt = 0;
				while((len = IoTUartRead(0, uartReadBuff, 1))<=0){
					timer_out_cnt++;
					if(timer_out_cnt>1000000){
						break;
					}
					osDelay(1);
				}
				if(len>0){
					board_type = uartReadBuff[0];
				}
				if(board_type != HARDWARE_TYPE){
					/* 类型不正确 */
					printf("FF%02X",HARDWARE_TYPE);
					continue;
				}

				if(len > 0 && sys_mode==PZ_SCRIPT_MODE){
					/* 脚本模式 */
	                printf(">>>");
	                int upload_file_fb = UtilsFileOpen("main.py", O_CREAT_FS | O_TRUNC_FS | O_WRONLY_FS, 0);
	                char *uartReadBuff = (char*)malloc(sizeof(char)*128);
					int lenBuf = 0;
					int recvlen = 0;
					FrameBufferStr *frame_handle = malloc(sizeof(FrameBufferStr));
					up_file_ctrl = malloc(sizeof(upload_file_pro_t));
					Sys_Debug_Init();
					PZ_SYS_DEBUG("start\r\n");
					if(up_file_ctrl!=NULL){
						memset(up_file_ctrl,0,sizeof(upload_file_pro_t));
						up_file_ctrl->fd = upload_file_fb;
						up_file_ctrl->loop_flag = 1;
						up_file_ctrl->success = 0;
						up_file_ctrl->last_id = 0xffff;
						up_file_ctrl->pre_id = 0x00;
						Init_Frame_Buffer(frame_handle,1024,up_file_protocal_cb);
						while(up_file_ctrl->loop_flag){ 
							recvlen = IoTUartRead(0, uartReadBuff, 128);
							Append_Frame_Buffer(frame_handle,(uint8_t*)uartReadBuff,recvlen);
							osDelay(1);
		                }
						if(up_file_ctrl->success==1){
							
							hi_reboot();
						}
						if(up_file_ctrl!=NULL){
							free(up_file_ctrl);
							up_file_ctrl=NULL;
						}
						if(frame_handle!=NULL){
							free(frame_handle);
							frame_handle = NULL;
						}
					}
	                write_bufIndex = 0;
	                write_uartIndex = 0;
	                writeLen = 0;
	                usleep(500000);
	                mp_deinit();
					//RebootDevice();
					
	                launch_python(false);
	                LOS_MuxPost(uartMux);
				}else if(len > 0 && sys_mode){
					/* 在线模式 */
					printf(">>>");
					/* 修改配置为在线模式 */
					polygon_cfg_t*sys_cfg =  get_sys_cfg();
					sys_cfg->sys_mode = PZ_ONLINE_MODE;
					update_sys_cfg(sys_cfg);
					/* 启动在线模式线程 */
					lunch_online();
					LOS_MuxPost(uartMux);
				}
                continue;
            }else if(len == 1 && uartReadBuff[0] == 3){
                if(thread_cnt > 0){
                    for(int i=0;i<thread_cnt;i++){
                        osThreadTerminate(thread_list[i]);
                        thread_list[i] = NULL;
                    }
                    thread_cnt = 0;
                }
				online_task_release();
#if ENABLE_MALLOC_HEAP
                if(heap != NULL){
                    free(heap);
                }
#endif
                write_bufIndex = 0;
                write_uartIndex = 0;
                writeLen = 0;
				all_peripheral_deinit();
                mp_deinit();
				polygon_cfg_t*sys_cfg =  get_sys_cfg();
				sys_cfg->sys_mode = PZ_SCRIPT_MODE;
				update_sys_cfg(sys_cfg);
                launch_python(true);
                LOS_MuxPost(uartMux);
                continue;
            }
            for(int i=write_bufIndex;i<len + write_bufIndex;i++){
                sharedUartReadBuff[i] = uartReadBuff[i - write_bufIndex];
            }
            write_bufIndex = write_bufIndex + len;
        }
        if(writeLen > 0){
            // printf("writeLen = %d\n",writeLen);
            IoTUartWrite(0, sharedUartWriteBuff, writeLen);
            write_uartIndex = 0;
            writeLen = 0;
        }
        LOS_MuxPost(uartMux);
        usleep(100);
    }
}








int main_entry() {
	hi_cpu_set_clk(HI_CPU_CLK_160M);
	
	unsigned int size;
    UartDemo_Entry();
	Sys_Debug_Init();
	int sys_mode = 0;
	polygon_cfg_t* cfg = get_sys_cfg();
	
	
	lunch_sys_cfg(cfg);
	
	//printf("cpu clk = %d\r\n",hi_cpu_get_clk());
	/*
	LOS_MEM_STATUS mem_status ;
	LOS_MemInfoGet(OS_SYS_MEM_ADDR, &mem_status);
	printf("free_size = %x\r\n",mem_status.freeSize);
	printf("free_size = %x\r\n",mem_status.freeCount);
	*/
	//OsMemInfoPrint(m_aucSysMem0);
	thread_list = (osThreadId_t *)malloc(sizeof(osThreadId_t)*20);
	/* 读取标记，判断是在线模式还是脚本模式,如果是在线模式则启动python线程 */
	if(cfg->sys_mode == 0){
		launch_python(false);
		
	}else{
		/* 否则启动在线模式线程 */
		lunch_online();
	}
    sys_thread();
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
