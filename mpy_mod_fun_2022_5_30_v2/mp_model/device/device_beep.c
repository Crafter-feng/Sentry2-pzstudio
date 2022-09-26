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
#include <string.h>
#include <stdio.h>
#include "py/obj.h"
#include "py/runtime.h"
#include "py/stream.h"
#include "py/builtin.h"
#include "iot_gpio.h" 
#include <unistd.h>
#include "los_mux.h"
#include "moddevice.h"
#include "modmachine.h"
#include <unistd.h>
#include "beep.h"
#include "decode.h"
#include "cmsis_os2.h" 


static int8_t new_class_flag = 0;
typedef struct _play_ctrl_t{
	struct _ctrl{
		unsigned char loop:1;
		unsigned char exit:1;
	}ctrl;
	unsigned char *music_data;
	unsigned char len;
}play_ctrl_t;



typedef struct _device_music_obj_t {
    mp_obj_base_t base;	
	struct _play_ctrl_t  *ctrl;
	UINT32 buzzerMux;
} device_music_obj_t;
osThreadId_t music_threadid;



MP_STATIC int device_beep_init(device_music_obj_t *self_in, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
	device_music_obj_t *self = MP_OBJ_TO_PTR(self_in);
	if(new_class_flag == 0){
		beep_init();
	   	beep_song_decode_init();
		if (self->buzzerMux == NULL){
        	if(LOS_MuxCreate(&(self->buzzerMux)) != LOS_OK){
				return -1;
			}
    	}
		self->ctrl = m_new(play_ctrl_t, 1);
		if(self->ctrl == NULL){
			return -1;
		}
		new_class_flag = 1;		
		return 0;
	}else{
		return -1;
	}
	
}




/******************************************************************************/
// MicroPython bindings for machine API
MP_STATIC void device_music_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    mp_printf(print, "buzzer music driver");
	
}




mp_obj_t device_music_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    mp_arg_check_num(n_args, n_kw, 0, 0, true);
	device_music_obj_t *self = m_new_obj(device_music_obj_t);
	if(self == NULL){
		mp_raise_msg(&mp_type_RuntimeError,MP_ERROR_TEXT("micropython run out of memory"));
	}
	self->base.type = type;
	int ret = device_beep_init(self, n_args - 1, all_args + 1, NULL);
	if(ret==0){
		return MP_OBJ_FROM_PTR(self);
	}else{
		m_del_obj(device_music_obj_t,self);
		return mp_const_none;
	}
}







static void stop_play_music(device_music_obj_t *self){
	if(music_threadid!=NULL){
		osThreadTerminate(music_threadid);
		music_threadid = NULL;
	}
	self->ctrl->ctrl.loop = 0;
	self->ctrl->ctrl.exit = 0;
	if(self->ctrl->music_data){
		m_free(self->ctrl->music_data);
		self->ctrl->music_data = NULL;
	}
	beep_off();
}





void exit_music_thread(){
	/* 退出线程 */
	if(music_threadid!=NULL){
		osThreadTerminate(music_threadid);
		music_threadid = NULL;
	}
	beep_off();
}




MP_STATIC mp_obj_t mp_device_music_init(mp_obj_t self_in) {
	/* 判断是否有后台线程，有则退出 */
	device_music_obj_t *self = MP_OBJ_TO_PTR(self_in);
	beep_init();
	beep_song_decode_init();
	stop_play_music(self);
	return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_device_music_init_obj, mp_device_music_init);







MP_STATIC mp_obj_t mp_device_music_deinit(mp_obj_t self_in) {
	device_music_obj_t *self = MP_OBJ_TO_PTR(self_in);
	stop_play_music(self);
	beep_deinit();
	return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_music_deinit_obj, mp_device_music_deinit);



void music_task(void *arg){
	int cnt =0;
	play_ctrl_t *ctrl = (play_ctrl_t*)arg;
	struct beep_song song;
	struct beep_song_data data={0};
	if(ctrl!=NULL &&  ctrl->music_data!=NULL){
		song.data = ctrl->music_data;
		song.len = beep_song_get_len(&song);
		while(cnt<song.len  &&  ctrl->ctrl.exit == 1){
			beep_song_get_data(&song, cnt, &(data));
			beep_set(data.freq, 50);
			usleep(data.sound_len*1000);
			beep_off();
			usleep(data.nosound_len*1000);
			cnt++;
		}
		
	}
	if(ctrl!=NULL){
		if(ctrl->music_data!=NULL){
			m_free(ctrl->music_data);
			ctrl->music_data = NULL;
		}
		ctrl->ctrl.exit=0;
		ctrl->len=0;
	}
	beep_off();
	osThreadTerminate(NULL);
}



int create_music_thread(void *arg){
    osThreadAttr_t attr = {0};
    attr.name = "music_Task";
    attr.attr_bits = 0U; 
    attr.cb_mem = NULL; 
    attr.cb_size = 0U; 
    attr.stack_mem = NULL; 
    attr.stack_size = 2048;//堆栈大小
    attr.priority = osPriorityNormal;//优先级 
	if(music_threadid!=NULL){
		osThreadTerminate(music_threadid);
		music_threadid = NULL;
	}
	music_threadid = osThreadNew((osThreadFunc_t)music_task, arg, &attr);
	if(music_threadid){
		return  0;
	}else{
		return -1;
	}
}





MP_STATIC mp_obj_t mp_device_music_play(size_t n_args, const mp_obj_t *args) {
	device_music_obj_t *self = MP_OBJ_TO_PTR(args[0]);
	#define HIVIEW_MS_PER_SECOND          1000
	mp_buffer_info_t song_buf;
	struct beep_song song;
	int loop_flag = mp_obj_get_int(args[2]);
	int cnt=0;
	struct beep_song_data data={0};
	LOS_MuxPend(self->buzzerMux, LOS_WAIT_FOREVER);
    mp_get_buffer_raise(args[1], &song_buf, MP_BUFFER_READ);
	if(song_buf.len>0 && song_buf.buf != NULL){
		self->ctrl->ctrl.exit = 1;
		if(loop_flag==1){
			song.data = song_buf.buf;
			song.len = beep_song_get_len(&song);
			while(cnt<song.len  &&  self->ctrl->ctrl.exit==1){
				beep_song_get_data(&song, cnt, &(data));
				beep_set(data.freq, 50);
				usleep(data.sound_len*1000);
				beep_off();
				usleep(data.nosound_len*1000);
				cnt++;
			}
			beep_off();
		}else{
			//后台播放
			/* 停止播放 */
			if(self->ctrl->music_data!=NULL){
				m_free(self->ctrl->music_data);
				self->ctrl->music_data = NULL;
			}
			self->ctrl->ctrl.exit = 1;
			self->ctrl->music_data = m_malloc(song_buf.len);
			if(self->ctrl->music_data != NULL){
				memcpy(self->ctrl->music_data,song_buf.buf,song_buf.len);
				self->ctrl->len = song_buf.len;
				if(create_music_thread(self->ctrl)==0){
					LOS_MuxPost(self->buzzerMux);
					return mp_const_true;
				}else{
					LOS_MuxPost(self->buzzerMux);
					return mp_const_false;
				}
				
			}else{
				LOS_MuxPost(self->buzzerMux);
				return mp_const_false;
			}
		}
	}
	LOS_MuxPost(self->buzzerMux);
    return mp_const_true;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_device_music_play_obj,3,3, mp_device_music_play);




MP_STATIC mp_obj_t mp_device_music_stop(mp_obj_t self_in) {
    device_music_obj_t *self = MP_OBJ_TO_PTR(self_in);
	stop_play_music(self);
	return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_music_stop_obj, mp_device_music_stop);



MP_STATIC mp_obj_t mp_device_beep_on(mp_obj_t self_in) {
    beep_on();
	return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_beep_on_obj, mp_device_beep_on);





MP_STATIC mp_obj_t mp_device_beep_off(mp_obj_t self_in) {
    beep_off();
	return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_device_beep_off_obj, mp_device_beep_off);





MP_STATIC const mp_rom_map_elem_t device_music_locals_dict_table[] = {
	{ MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mp_device_music_init_obj) },
	{ MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&mp_device_music_deinit_obj) },
	{ MP_ROM_QSTR(MP_QSTR_on), MP_ROM_PTR(&mp_device_beep_on_obj) },
    { MP_ROM_QSTR(MP_QSTR_off), MP_ROM_PTR(&mp_device_beep_off_obj) },
    { MP_ROM_QSTR(MP_QSTR_player), MP_ROM_PTR(&mp_device_music_play_obj) },
    { MP_ROM_QSTR(MP_QSTR_stop), MP_ROM_PTR(&mp_device_music_stop_obj) },
};
MP_DEFINE_CONST_DICT(mp_device_music_locals_dict, device_music_locals_dict_table);





const mp_obj_type_t device_beep_type = {
    { &mp_type_type },
    .name = MP_QSTR_BEEP,
    .print = device_music_print,
    .make_new = device_music_make_new,
    .locals_dict = (mp_obj_dict_t *)&mp_device_music_locals_dict,
};








