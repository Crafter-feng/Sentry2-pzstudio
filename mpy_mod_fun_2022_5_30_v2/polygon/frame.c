
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


/* Includes  == 文件包含 --------------------------------------------*/
#include "frame.h"





/* Private typedef    ==  私有类型 ----------------------------------*/
/* Private define     ==  私有定义 ----------------------------------*/



/* Private macro      ==  私有宏 ------------------------------------*/
/* Private variables  ==  私有变量 ----------------------------------*/



/* Private functions  ==  私有函数定义 ------------------------------*/

/**********************************************************************
* @Fuctionname   : None
* @Brief         : None
* @Input         : None
* @Output        : None
* @Return        : None
* @Remark        : None
**********************************************************************/
void Init_Frame_Buffer(FrameBufferStr *frame, uint16 buffer_length, FRAME_VALIDATE validate_proc)
{
	frame->buffer = malloc(buffer_length * sizeof(uint8));
	frame->head = 0;
	frame->count = 0;
	frame->BUFFERLENGTH = buffer_length;
	frame->ValidateFrame = validate_proc;
}



/**********************************************************************
* @Fuctionname   : None
* @Brief         : None
* @Input         : None
* @Output        : None
* @Return        : None
* @Remark        : None
**********************************************************************/
void Deinit_Frame_Buffer(FrameBufferStr *frame)
{
	if(frame->buffer!=NULL)
		free(frame->buffer);
}



/**********************************************************************
* @Fuctionname   : None
* @Brief         : None
* @Input         : None
* @Output        : None
* @Return        : None
* @Remark        : None
**********************************************************************/
void Append_Frame_Clean(FrameBufferStr *frame)
{
	memset(frame->buffer, 0, frame->BUFFERLENGTH);
	frame->head = 0;
	frame->count = 0;

}

/**********************************************************************
* @Fuctionname   : None
* @Brief         : None
* @Input         : None
* @Output        : None
* @Return        : None
* @Remark        : None
**********************************************************************/

void Append_Frame_Buffer(FrameBufferStr *frame, uint8 *input, uint16 length)
{ 
	uint16 i = 0;
	//s16 head=0;
  uint16 mlen=0;
	
	// 如果上传数据长度比缓存总长度还要长
	if (length > frame->BUFFERLENGTH)
	{
		// 此处可添加错误代码
		return;
	}
	
	if((uint16)frame->count + length > frame->BUFFERLENGTH)
	{
		memmove(frame->buffer, frame->buffer+frame->head, frame->count - frame->head);
		frame->count = frame->count - frame->head;
		frame->head = 0;	
		memset(frame->buffer + frame->count, 0, frame->BUFFERLENGTH - frame->count);
		if((frame->count + length) > frame->BUFFERLENGTH)
		{
			// index out of buffer range
			frame->count=0;
			frame->head=0;
			return;
		}
	}

//	if(length != 0)
	{
		memcpy(frame->buffer+frame->count, input, length);
		frame->count+=length;
	}

	i = 0;
	
	//while(frame->head + i < frame->count)
	{
		
		mlen = frame->ValidateFrame(frame->buffer + frame->head, frame->count - frame->head);
		if(mlen > 0)
		 {
			if(mlen > frame->BUFFERLENGTH)
			{
				frame->head = 0;
				frame->count = 0;	
				memset(frame->buffer, 0, frame->BUFFERLENGTH);
                return ;
				//break;
			}
			/* 将不是 0xA5 0x5A 的数据 返回给上过滤给上一层(input) */
			/* 将flag 置 0 */
			frame->head = frame->head+ mlen;		
			if(frame->head > frame->count)
			{
				frame->count = frame->head;
			}
			
			if(frame->head == frame->count)
			{
				frame->head = 0;
				frame->count = 0;	
				memset(frame->buffer, 0, frame->BUFFERLENGTH);
				//break;
                return ;
			}
		}	
	}

}


/*********************************  COPYRIGHT 2019 --------  *********  END OF FILE  **********************************/
