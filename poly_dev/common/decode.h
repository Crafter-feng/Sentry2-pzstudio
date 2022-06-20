/*
* Copyright (c) 2006-2018, RT-Thread Development Team
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date           Author       Notes
* 2018-10-17     flybreak      the first version
*/

#ifndef DECODE_H
#define DECODE_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>



#define SEMIBREVE_LEN 1600
/****    播放效果     ****/
#define SOUND_SIGNATURE       0    //调号：升0个半音
#define SOUND_OCTACHORD       2    //升降八度：升一个八度
#define SOUND_SPACE           4/5  //定义普通音符演奏的长度分率,//每4分音符间隔

#define SONG_NAME_LENGTH_MAX  30
#define SONG_DATA_LENGTH_MAX  200

struct beep_song
{
    //const unsigned char name[SONG_NAME_LENGTH_MAX];
    unsigned short len;
    unsigned char *data;//[SONG_DATA_LENGTH_MAX];
};

struct beep_song_data
{
    unsigned short freq;
    unsigned short sound_len;
    unsigned short nosound_len;
};

int beep_song_decode_init(void);
unsigned short beep_song_get_len(const struct beep_song *song);
int beep_song_get_name(const struct beep_song *song, char *name);
unsigned short beep_song_get_data(const struct beep_song *song, unsigned short index, struct beep_song_data *data);

#endif
