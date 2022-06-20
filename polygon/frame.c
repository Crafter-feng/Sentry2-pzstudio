
/*********************************  COPYRIGHT 2019 --------  *********  BEGIN OF FILE  ********************************/

/**********************************************************************
* @file           : frame.h
* @author         : --
* @version        : --
* @date           : 2019-11-19
* @brief          : frame program body
* @Description    : --
**********************************************************************/

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
	
	while(frame->head + i < frame->count)
	{
		
		mlen = frame->ValidateFrame(frame->buffer + frame->head + i, frame->count - frame->head - i);
		if(mlen > 0)
		 {
			if(mlen > frame->BUFFERLENGTH)
			{
				frame->head = 0;
				frame->count = 0;	
				memset(frame->buffer, 0, frame->BUFFERLENGTH);
				break;
			}
			frame->head = frame->head + i + mlen;		
			if(frame->head > frame->count)
			{
				frame->count = frame->head;
			}
			i = 0;
			if(frame->head == frame->count)
			{
				frame->head = 0;
				frame->count = 0;	
				memset(frame->buffer, 0, frame->BUFFERLENGTH);
				break;
			}
		}
		else
		{
			i++;	
		}		
	}

}


/*********************************  COPYRIGHT 2019 --------  *********  END OF FILE  **********************************/
