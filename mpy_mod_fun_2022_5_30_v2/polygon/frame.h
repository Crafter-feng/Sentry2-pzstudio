
/*********************************  COPYRIGHT 2015 --------  *********  BEGIN OF FILE  ********************************/

/**********************************************************************
* file           : frame.h
* author         : --
* version        : --
* date           : 2015-03-12
* brief          : Header for frame.c module
* Description    : --
**********************************************************************/

/* Define to prevent recursive inclusion ----------------------------*/
#ifndef __FRAME_H
#define __FRAME_H

 

/* Includes  == 文件包含 --------------------------------------------*/
#include "ohos_types.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Private typedef    ==  私有类型 ----------------------------------*/
/* Private define     ==  私有定义 ----------------------------------*/
typedef uint16(*FRAME_VALIDATE)(uint8 *frame_buf, uint16 remaining_length);

typedef  struct
{
	uint8 *buffer;
	uint16 head;
	uint16 count;
	uint16 BUFFERLENGTH;
	FRAME_VALIDATE ValidateFrame;
} FrameBufferStr;


/* Private macro      ==  私有宏 ------------------------------------*/
/* Private variables  ==  私有变量 ----------------------------------*/



/* Private function prototypes  ==  私有函数声明 --------------------*/
void Init_Frame_Buffer(FrameBufferStr *frame, uint16 buffer_length, FRAME_VALIDATE validate_proc);
void Deinit_Frame_Buffer(FrameBufferStr *frame);
void Append_Frame_Buffer(FrameBufferStr *frame, uint8 *input, uint16 length);
void Append_Frame_Clean(FrameBufferStr *frame);


/* Define to prevent recursive inclusion ----------------------------*/
#endif /* __FRAME_H */




/*********************************  COPYRIGHT 2015 --------  *********  END OF FILE  **********************************/
