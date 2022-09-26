
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





#ifndef MUSIC_PLAY_H
#define MUSIC_PLAY_H



#include <stdio.h>
#include "esp_system.h"
#include "esp_log.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "decode.h"




typedef struct{
	/* 播放的乐曲 */
	const struct beep_song* song;
	/* 播放乐曲的长度 */
	int music_len;
	/* 当前需要播放的数据 */
	struct beep_song_data data;
	/* 当前播放的计数 */
	int cnt;
}Song_Ctrl_t;


typedef enum{
	/* 初始化状态 */
	PLAYER_INIT = 0,
	PLAYER_SONG,
}Play_Ctrl_Status_t;



typedef enum {
    PLAYER_RUNNING, //正在播放
    PLAYER_STOP     //播放停止
}Play_status_t;






typedef struct{
	/* 播放的状态机 */
	Play_Ctrl_Status_t ctrl_status;
	/* 当前的播放状态 */
	Play_status_t play_status; 	
	/* 当前播放的歌曲 */
	int song_current; 
	/* mp3 任务创建标志 */
	int task_is_create;
	/* 获取播放标志 */
	int play_finsh;
}Play_Ctrl_t;



int Music_Init(void);
int music_select(int track,int progress);
int music_get_progres(int *track, int *progress);


int music_is_finsh(void);
void music_stop(void);


#endif


