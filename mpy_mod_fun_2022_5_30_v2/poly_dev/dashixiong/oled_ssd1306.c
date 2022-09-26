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
 
 
 

#include <stddef.h>
#include <stdio.h>
#include <math.h>
#if BUILD_BOARD == DASHIXIONG_BOARD
#include "oled_ssd1306.h"
#include "iot_gpio.h"
#include "iot_i2c.h"
#include "iot_errno.h"
#include "sys_debug.h"
#include "hal_pz_i2c.h"
#include "encode_convert.h"
#include "gb2312_font.h"


#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

#define OLED_I2C_IDX 0

#define OLED_WIDTH    (128)
#define OLED_I2C_ADDR 0x3c // 默认地址为 0x78

#define OLED_I2C_BAUDRATE (400*1000) // 400k


#define SSD1306_CTRL_CMD 0x00
#define SSD1306_CTRL_DATA 0x40
#define SSD1306_MASK_CONT (0x1<<7)



static int8_t oled_i2c_id;
static uint8_t oled_i2c_addr;
const static uint8_t oled_flush_cmd[] = {
        0X21,   // 设置列起始和结束地址
        0X00,   // 列起始地址 0
        0X7F,   // 列终止地址 127
        0X22,   // 设置页起始和结束地址
        0X00,   // 页起始地址 0
        0X07,   // 页终止地址 7
};



void set_oled_i2c_arg(int8_t i2c_id, uint8_t i2c_addr){
	oled_i2c_id = i2c_id;
	oled_i2c_addr = i2c_addr;
	
}




static uint32_t ssd1306_SendData(uint8_t* data, size_t size)
{
    return hal_pz_i2c_write(oled_i2c_id,oled_i2c_addr,data, size);
}




static uint32_t I2cWiteByte(uint8_t regAddr, uint8_t byte)
{
	#if 1
    uint8_t buffer[] = {regAddr, byte}; 
    uint8_t sendLen = sizeof(buffer)/sizeof(buffer[0]);
	return hal_pz_i2c_write(oled_i2c_id,oled_i2c_addr,buffer, sendLen);
	#endif
	
    
}



static uint32_t ssd1306_WiteByte(uint8_t regAddr, uint8_t byte)
{
    uint8_t buffer[] = {regAddr, byte};
    return ssd1306_SendData(buffer, sizeof(buffer));
}

// Send a byte to the command register
uint32_t ssd1306_WriteCommand(uint8_t byte) {
    ssd1306_WiteByte(SSD1306_CTRL_CMD, byte);
}











// Send data
void ssd1306_WriteData(uint8_t* buffer, size_t buff_size) {
    uint8_t data[SSD1306_WIDTH * 2] = {0};
    for (size_t i = 0; i < buff_size; i++) {
        data[i*2] = SSD1306_CTRL_DATA | SSD1306_MASK_CONT;
        data[i*2+1] = buffer[i];
    }
    data[(buff_size - 1) * 2] = SSD1306_CTRL_DATA;
    ssd1306_SendData(data, sizeof(data));
}




static SSD1306_t SSD1306;



uint32_t OledInit(int8_t i2c_id, uint8_t i2c_addr,uint32_t baudrate)
{
	set_oled_i2c_arg(i2c_id,i2c_addr);
	
    static const uint8_t initCmds[] = {
        0xAE,    //关闭显示
        0x20,    //设置时钟分频因子,震荡频率
        0x00,    //[3:0],分频因子;[7:4],震荡频率
        0xB0,    //设置驱动路数
        0xC8,    //默认0X3F(1/64) 
		0x00,
		0x10,
		0x40,
		0x81,
		0xFF,
		0xA1,
		0xA6,
		0xFF,
		0x3F,
		0xA4,
		0xD3,
		0x00,
		0xD5,
		0xF0,
		0xD9,
		0x11,
		0xDA,
		0x12,
		0xDB,
		0x30,
		0x8D,
		0x14,
		
    };
   int ret = hal_pz_i2c_init(i2c_id,baudrate);
   
   if(ret!=0){
		return ret;
   }


   //printf("addr = %d, id = %d\r\n",oled_i2c_addr,oled_i2c_id);
   for (size_t i = 0; i < ARRAY_SIZE(initCmds); i++) {
		uint32_t status = ssd1306_WriteCommand(initCmds[i]);
		if (status != IOT_SUCCESS) {
			//printf("i=%d\r\n",i);
		    return status;
		}
   }
   /* 清屏 */
   ssd1306_SetDisplayOn(1);
   /* 分配内存 */
   if(SSD1306.Initialized == 0 && SSD1306.data == NULL){
   		SSD1306.data_len = sizeof(oled_flush_cmd)*2 + SSD1306_BUFFER_SIZE + 1;
   		SSD1306.data = malloc(SSD1306.data_len);
		if(SSD1306.data == NULL){
			return -1;
		}
		
		
   }
   SSD1306.head_index = 0;
   if(SSD1306.data != NULL){
		for (uint32_t i = 0; i < sizeof(oled_flush_cmd)/sizeof(oled_flush_cmd[0]); i++) {
	        SSD1306.data[SSD1306.head_index++] = SSD1306_CTRL_CMD | SSD1306_MASK_CONT;
	        SSD1306.data[SSD1306.head_index++] = oled_flush_cmd[i];
    	}

    	// copy frame data
    	SSD1306.data[SSD1306.head_index++] = SSD1306_CTRL_DATA;
		SSD1306.buf = &SSD1306.data[SSD1306.head_index];
   }
   ssd1306_Fill(Black);
   ssd1306_UpdateScreen();
   return IOT_SUCCESS;
}




uint32_t OledDeinit(void){
    hal_pz_i2c_deinit(oled_i2c_id);
	oled_i2c_id  =  0;
	oled_i2c_addr = 0;
	if(SSD1306.data!=NULL){
		SSD1306.buf = NULL;
		free(SSD1306.data);
		SSD1306.data = NULL;
	}
	SSD1306.Initialized = 0;
}






void ssd1306_Fill(SSD1306_COLOR color) {
    /* Set memory */
    uint32_t i;
	if(SSD1306.buf == NULL){
		return ;
	}
    for(i = 0; i < SSD1306_BUFFER_SIZE; i++) {
        SSD1306.buf[i] = (color == Black) ? 0x00 : 0xFF;
    }
}





// Write the screenbuffer with changed to the screen
void ssd1306_UpdateScreen(void) {
    // Write data to each page of RAM. Number of pages
    // depends on the screen height:
    //
    //  * 32px   ==  4 pages
    //  * 64px   ==  8 pages
    //  * 128px  ==  16 pages

    if(SSD1306.buf == NULL || SSD1306.data == NULL){
		return ;
	}
    

    // send to i2c bus
    uint32_t retval = ssd1306_SendData(SSD1306.data, SSD1306.data_len);
	
    if (retval != 0) {
        //printf("ssd1306_UpdateScreen send frame data filed: %d!\r\n", retval);
    }
	
	
}







//    Draw one pixel in the screenbuffer
//    X => X Coordinate
//    Y => Y Coordinate
//    color => Pixel color
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color) {
	if(SSD1306.buf == NULL){
		return ;
	}
	if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) {
        // Don't write outside the buffer
        return;
    }
    // Check if pixel should be inverted
    if(SSD1306.Inverted) {
        color = (SSD1306_COLOR)!color;
    }
    // Draw in the right color
    if(color == White) {
        SSD1306.buf[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
    } else {
        SSD1306.buf[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
}




// Draw 1 char to the screen buffer
// ch       => char om weg te schrijven
// Font     => Font waarmee we gaan schrijven
// color    => Black or White
#if 0
char ssd1306_DrawChar(char ch, FontDef Font, SSD1306_COLOR color) {
    uint32_t i, b, j;

    // Check if character is valid
    if (ch < 32 || ch > 126)
        return 0;

    // Check remaining space on current line
    if(SSD1306_WIDTH < (SSD1306.CurrentX + Font.FontWidth)){
		SSD1306.CurrentX = 0;
		SSD1306.CurrentY += Font.FontHeight;
	}
    if (SSD1306_HEIGHT < (SSD1306.CurrentY + Font.FontHeight))
    {
        // Not enough space on current line
        return 0;
    }

    // Use the font to write
    for(i = 0; i < Font.FontHeight; i++) {
        b = Font.data[(ch - 32) * Font.FontHeight + i];
        for(j = 0; j < Font.FontWidth; j++) {
            if((b << j) & 0x8000)  {
                ssd1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR) color);
            } else {
                ssd1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR)!color);
            }
        }
    }

    // The current space is now taken
    SSD1306.CurrentX += Font.FontWidth;

    // Return written char for validation
    return ch;
}
#endif
//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16/24
//mode:叠加方式(1)还是非叠加方式(0)

void ssd1306_DrawChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode,SSD1306_COLOR color)
{  				
    uint8_t  temp,t1,t;
	uint16_t y0=y;
	uint8_t  csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数	
	if(size!=12){
		return;
	}
	mode = mode;
	num=num-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	if(num>=95){
		return ;
	}
	for(t=0;t<csize;t++)
	{   
		temp=asc2_1206[num][t];
		//if(size==12)temp=asc2_1206[num][t]; 	 	//调用1206字体
		//else if(size==16)temp=asc2_1608[num][t];	//调用1608字体
		//else if(size==24)temp=asc2_2412[num][t];	//调用2412字体
		//else return;								//没有的字库
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)ssd1306_DrawPixel(x,y,color);
			else if(mode==0)ssd1306_DrawPixel(x,y,!color);
			temp<<=1;
			y++;
			if(y>=SSD1306_HEIGHT)return;		//超区域了
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=SSD1306_WIDTH)return;	//超区域了
				break;
			}
		}  	 
	}  	    	   	 	  
}  



const unsigned char chinese_text_test[3][24]={
	
	{0x7f,0xc0,0x40,0x80,0x7f,0xc0,0x0,0x0,0x7f,0xf0,0x4c,0x40,0x73,0x80,0x1f,0x0,0x51,0x10,0x7f,0xf0,0x40,0x0,0x0,0x0,},//0xa1b0
	{0x08,0x10,0x88,0x20,0x4F,0xC0,0x00,0x20,0x10,0x50,0x11,0x90,0xFE,0x10,0x10,0x50,0x10,0x50,0x10,0x50,0x1F,0x90,0x00,0x00},/*"边",1*/
	{0x44,0x10,0x7F,0xE0,0x44,0x00,0x44,0x00,0x7F,0xF0,0x44,0x00,0x00,0x10,0x11,0x10,0x22,0x20,0xC4,0x40,0x18,0x80,0x00,0x00},/*"形",2*/
	
};



void Show_Font(uint16_t x,uint16_t y,uint8_t *font,uint8_t size,uint8_t mode,SSD1306_COLOR color)
{
	uint8_t temp,t,t1;
	uint16_t y0=y;
	uint8_t *dzk;   
	uint8_t csize=(size/8+((size%8)?1:0))*(size);//得到字体一个字符对应点阵集所占的字节数	 
	if(size!=12)return;	//不支持的size
	//Get_HzMat(font,dzk,size);	//得到相应大小的点阵数据 
	dzk = font;
	for(t=0;t<csize;t++)
	{   												   
		temp=dzk[t];			//得到点阵数据                          
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)ssd1306_DrawPixel(x,y,color);
			else if(mode==0)ssd1306_DrawPixel(x,y,!color); 
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
	}  
}



void Get_HzMat(unsigned char *_src_code,unsigned char *mat,uint8_t size)
{		    
	unsigned char qh,ql;
	unsigned char i;					  
	unsigned long foffset; 
	unsigned char *code = _src_code;
	uint8_t csize=(size/8+((size%8)?1:0))*(size);//得到字体一个字符对应点阵集所占的字节数	 
	qh=*code;
	ql=*(++code);
	if(qh<0x81||ql<0x40||ql==0xff||qh==0xff)//非 常用汉字
	{   		    
	    //for(i=0;i<csize;i++)*mat++=0x00;//填充满格
	    return; //结束访问
	}          
	if(ql<0x7f)ql-=0x40;//注意!
	else ql-=0x41;
	qh-=0x81;   
	foffset=((unsigned long)qh+ql)*csize;	//得到字库中的字节偏移量 
	printf("foffset = %d\r\n",foffset);
	switch(size)
	{
        
		case 12:
			//SPI_Flash_Read(mat,foffset+ftinfo.f12addr,24);
			break;
		case 16:
			//SPI_Flash_Read(mat,foffset+ftinfo.f16addr,32);
			break;
		case 24:
			//SPI_Flash_Read(mat,foffset+ftinfo.f24addr,72);
			break;
			
	}     												    
}  

void ssd1306_Show_Str(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t*str,uint8_t size,uint8_t mode,SSD1306_COLOR color)
{					
	uint16_t x0=x;
	uint16_t y0=y;
	
	#if 1
    //字符或者中文
    unsigned long strUnicode1[2]={0x00};
	unsigned short strUnicode[2] = {0x00};
	char strGbk[5]={0x00};
	int unicode_len , gbk_len;
	if(str != NULL){
		while(*str!=0){
			unicode_len = Utf8ToUnicode(str,strUnicode1);
			if(unicode_len == 0){
				str++;
				continue;
			}
			//printf("unicode_len = %d\r\n",unicode_len);
			if(unicode_len == 1){
				/*aciss 码显示*/
				if(((*str) == '\n') || ((*str) == '\r')){
					y+=size;
					x=x0;
					str++;
					if(((*str)=='\r') || ((*str)=='\n')){
						str++;
					}
					continue;
				}
				if(x>(x0+width-size/2))//换行
				{				   
					y+=size;
					x=x0;	   
				}
				
		        if(y>(y0+height-size)){
					//越界
				}      
		        if(*str==13)//换行符号
		        {         
		            y+=size;
					x=x0;
		        }  
		        else{ 
					ssd1306_DrawChar(x,y,*str,size,mode,color);//有效部分写入 
		        	x+=size/2; //字符,为全字的一半 
		        }
			}
			else{
				/* 中文 */
				strUnicode[0] = (unsigned short)strUnicode1[0];
				gbk_len = UnicodeToGbk(strUnicode,strGbk,5);
				unsigned char* p = (unsigned char*)strGbk;  
				
				if(gbk_len==2){
					uint8_t *code_mat = NULL;
					//printf("%x\r\n",((*p)<<8)|(*(p+1)));
					#if 1
					uint8_t area_code = (*p)-(0xa0);
					if(1<=area_code&&area_code<=3){
						uint8_t qh =  (area_code-1);
						uint8_t ql =  ((*(p+1)) - (0xa0));
						uint16_t biaodian_offset = (qh*94)+(ql-1)-1;
						//printf("biaodian_offset = %d\r\n",biaodian_offset);
						if(biaodian_offset<218){
							code_mat=gb2312_biaodian_list[biaodian_offset];
						}
					}
					else if(16 <= area_code && area_code <= 87){
						/* 中文字编码 */
						uint8_t qh =  (area_code)-16;
						uint8_t ql =  ((*(p+1)) - (0xa0));
						uint16_t gb2312_offset = (qh*94)+(ql-1);
						if(gb2312_offset<6768){
							code_mat = gb2312_list[gb2312_offset];
							
						}
					}
					if(code_mat!=NULL){
						if(x>(x0+width-size))//换行
						{				   
							y+=size;
							x=x0;	   
						}
						if(y>(y0+height-size)){
							//越界返回
						}else{
							Show_Font(x,y,code_mat,size,mode,color);
							x+=size;
						}
						
					}
					#endif
				}
			}
			str += unicode_len;
		}
	}
	#endif
	
} 





void ssd1306_Show_Str_Line(uint8_t line, uint8_t*str,uint8_t size,SSD1306_COLOR color){
	line %=6;
	if(line>0){
		line -= 1;
	}
	uint16_t y = line*size;
	ssd1306_Show_Str(0,y,SSD1306_WIDTH,SSD1306_HEIGHT,str,size,0,color);
}



void ssd1306_fill_screen_line(int line,SSD1306_COLOR color){
	line %=6;
	if(line>0){
		line -= 1;
	}
	
	uint16_t y = line*12;
	ssd1306_FillRectangle(0,y,SSD1306_WIDTH,11,color);
	
}






#if 0
// Write full string to screenbuffer
char ssd1306_DrawString(char* str, FontDef Font, SSD1306_COLOR color) {
    // Write until null-byte
    //Utf8ToUnicode(str)
    while (*str) {
        if (ssd1306_DrawChar(*str, Font, color) != *str) {
            // Char could not be written
            return *str;
        }

        // Next char
        str++;
    }

    // Everything ok
    return *str;
}
#endif



// Position the cursor
void ssd1306_SetCursor(uint8_t x, uint8_t y) {
    SSD1306.CurrentX = x;
    SSD1306.CurrentY = y;
}


//快速划线 专用于画横平竖直的线 提高效率
void ssd1306_DrawHLine(uint8_t x1, uint8_t y1, uint8_t w,SSD1306_COLOR color)
{
	int end = x1+w;
	int start;
	
	for (start = x1; start < end; start++)
	{
		ssd1306_DrawPixel(start, y1, color);
	}
}


//快速划线 专用于画横平竖直的线 提高效率
void ssd1306_DrawVLine(uint8_t x1, uint8_t y1, uint8_t h,SSD1306_COLOR color)
{
	int end = y1+h;
	int start;
	for (start = y1; start < end; start++)
	{
		ssd1306_DrawPixel(x1, start, color);
	}
}




// Draw line by Bresenhem's algorithm
void ssd1306_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color) {
  int32_t deltaX = abs(x2 - x1);
  int32_t deltaY = abs(y2 - y1);
  int32_t signX = ((x1 < x2) ? 1 : -1);
  int32_t signY = ((y1 < y2) ? 1 : -1);
  int32_t error = deltaX - deltaY;
  int32_t error2;

  ssd1306_DrawPixel(x2, y2, color);
    while((x1 != x2) || (y1 != y2))
    {
    ssd1306_DrawPixel(x1, y1, color);
    error2 = error * 2;
    if(error2 > -deltaY)
    {
      error -= deltaY;
      x1 += signX;
    }
    else
    {
    /*nothing to do*/
    }

    if(error2 < deltaX)
    {
      error += deltaX;
      y1 += signY;
    }
    else
    {
    /*nothing to do*/
    }
  }
  return;
}






/* 画虚线 */
void ssd1306_DrawDottedLine(int16_t iStartX, int16_t iStartY, int16_t iEndX, int16_t iEndY,SSD1306_COLOR color)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    int16_t  iDx, iDy;
    int16_t  iIncX, iIncY;
    int16_t  iErrX = 0, iErrY = 0;
    int16_t  iDs;
    int16_t  iCurrentPosX, iCurrentPosY;
    uint16_t Dotted_piont = 1;
    bool point = 1;
    /*----------------------------------*/
    /* Initialize						*/
    /*----------------------------------*/
    iErrX = 0;
    iErrY = 0;
    iDx = iEndX - iStartX; //X轴差值
    iDy = iEndY - iStartY; //Y轴差值
    iCurrentPosX = iStartX;
    iCurrentPosY = iStartY;

    if(iDx > 0) //X轴差值大于0
    {
        iIncX = 1;
    }
    else
    {
        if(iDx == 0) //X轴差值等于0
        {
            iIncX = 0;
        }
        else   //X轴差值小于0
        {
            iIncX = -1;
            iDx = -iDx; //iDx取反
        }
    }

    if(iDy > 0) //Y轴差值大于0
    {
        iIncY = 1;
    }
    else
    {
        if(iDy == 0) //Y轴差值等于0
        {
            iIncY = 0;
        }
        else    //Y轴差值小于0
        {
            iIncY = -1;
            iDy = -iDy;
        }
    }

    if(iDx > iDy) //斜率小于45°
    {
        iDs = iDx;
    }
    else     //斜率大于等于45°
    {
        iDs = iDy;
    }

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    for(uint8_t i = 0; i <= iDs+1; i++)
    {
    	if(color == Black){
			point = 0;
		}
        ssd1306_DrawPixel(iCurrentPosX,iCurrentPosY, point);//当前位置画点
        iErrX += iDx; //X轴偏移
        if(iErrX > iDs)
        {
            iErrX -= iDs;
            iCurrentPosX += iIncX;
        }
        iErrY += iDy; //Y轴偏移
        if(iErrY > iDs)
        {
            iErrY -= iDs;
            iCurrentPosY += iIncY;
        }
        if(++Dotted_piont && Dotted_piont%3 == 0)//计算虚线间隔
        {
            point = !point;
        }
    }
}



//Draw polyline
void ssd1306_DrawPolyline(const SSD1306_VERTEX *par_vertex, uint16_t par_size, SSD1306_COLOR color) {
  uint16_t i;
  if(par_vertex != 0){
    for(i = 1; i < par_size; i++){
      ssd1306_DrawLine(par_vertex[i - 1].x, par_vertex[i - 1].y, par_vertex[i].x, par_vertex[i].y, color);
    }
  }
  else
  {
    /*nothing to do*/
  }
  return;
}





/*Convert Degrees to Radians*/
static float ssd1306_DegToRad(float par_deg) {
    return par_deg * 3.14 / 180.0;
}





/*Normalize degree to [0;360]*/
static uint16_t ssd1306_NormalizeTo0_360(uint16_t par_deg) {
  uint16_t loc_angle;
  if(par_deg <= 360)
  {
    loc_angle = par_deg;
  }
  else
  {
    loc_angle = par_deg % 360;
    loc_angle = ((par_deg != 0)?par_deg:360);
  }
  return loc_angle;
}



/*DrawArc. Draw angle is beginning from 4 quart of trigonometric circle (3pi/2)
 * start_angle in degree
 * sweep in degree
 */
void ssd1306_DrawArc(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR color) {
    #define CIRCLE_APPROXIMATION_SEGMENTS 36
    float approx_degree;
    uint32_t approx_segments;
    uint8_t xp1,xp2;
    uint8_t yp1,yp2;
    uint32_t count = 0;
    uint32_t loc_sweep = 0;
    float rad;
    loc_sweep = ssd1306_NormalizeTo0_360(sweep);
    count = (ssd1306_NormalizeTo0_360(start_angle) * CIRCLE_APPROXIMATION_SEGMENTS) / 360;
    approx_segments = (loc_sweep * CIRCLE_APPROXIMATION_SEGMENTS) / 360;
    approx_degree = loc_sweep / (float)approx_segments;
    while(count < approx_segments)
    {
        rad = ssd1306_DegToRad(count*approx_degree);
        xp1 = x + (int8_t)(sin(rad)*radius);
        yp1 = y + (int8_t)(cos(rad)*radius);
        count++;
        if(count != approx_segments)
        {
            rad = ssd1306_DegToRad(count*approx_degree);
        }
        else
        {
            rad = ssd1306_DegToRad(loc_sweep);
        }
        xp2 = x + (int8_t)(sin(rad)*radius);
        yp2 = y + (int8_t)(cos(rad)*radius);
        ssd1306_DrawLine(xp1,yp1,xp2,yp2,color);
    }
	
    return;
}








////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//画部分圆
//圆心坐标 半径 4份圆要画哪一份或哪几份
void ssd1306_DrawCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername,SSD1306_COLOR color)
{
	int f = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int x = 0;
	int y = r;
	while (x<y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}

		x++;
		ddF_x += 2;
		f += ddF_x;

		if (cornername & 0x4)//右上
		{
			//此处画圆的方式是交替打点 从2边打到中间 最终x<y就打完点跳出循环
			ssd1306_DrawPixel(x0 + x, y0 + y,color);
			ssd1306_DrawPixel(x0 + y, y0 + x,color);
		}
		if (cornername & 0x2)//右下
		{
			ssd1306_DrawPixel(x0 + x, y0 - y, color);
			ssd1306_DrawPixel(x0 + y, y0 - x, color);
		}
		if (cornername & 0x8)//左上
		{
			ssd1306_DrawPixel(x0 - y, y0 + x, color);
			ssd1306_DrawPixel(x0 - x, y0 + y, color);
		}
		if (cornername & 0x1)//左下
		{
			ssd1306_DrawPixel(x0 - y, y0 - x, color);
			ssd1306_DrawPixel(x0 - x, y0 - y, color);
		}
	}
}








//填充2个四分之一圆和中间的矩形
//此函数专用于画圆角矩形
//右上四分之一圆或左下四分之一圆的圆心 半径 中间矩形的高
void ssd1306_DrawFillCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername, int delta,SSD1306_COLOR color)
{
	int f = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int x = 0;
	int y = r;
	while (x < y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		if (cornername & 0x1)//填充右边的2个四分之一圆和中间的矩形
		{
			ssd1306_DrawVLine(x0+x, y0-y, 2*y+1+delta,color);
			ssd1306_DrawVLine(x0+y, y0-x, 2*x+1+delta,color);
		}
		if (cornername & 0x2)//填充左边的2个四分之一圆和中间的矩形
		{
			ssd1306_DrawVLine(x0-x, y0-y, 2*y+1+delta,color);
			ssd1306_DrawVLine(x0-y, y0-x, 2*x+1+delta,color);
		}
	}
}




//Draw circle by Bresenhem's algorithm
void ssd1306_DrawCircle(uint8_t par_x,uint8_t par_y,uint8_t par_r,SSD1306_COLOR par_color) {
  int32_t x = -par_r;
  int32_t y = 0;
  int32_t err = 2 - 2 * par_r;
  int32_t e2;
  if (par_x >= SSD1306_WIDTH || par_y >= SSD1306_HEIGHT) {
    return;
  }
  do {
      ssd1306_DrawPixel(par_x - x, par_y + y, par_color);
      ssd1306_DrawPixel(par_x + x, par_y + y, par_color);
      ssd1306_DrawPixel(par_x + x, par_y - y, par_color);
      ssd1306_DrawPixel(par_x - x, par_y - y, par_color);
        e2 = err;
        if (e2 <= y) {
            y++;
            err = err + (y * 2 + 1);
            if(-x == y && e2 <= x) {
              e2 = 0;
            }
            else
            {
              /*nothing to do*/
            }
        }
        else
        {
          /*nothing to do*/
        }
        if(e2 > x) {
          x++;
          err = err + (x * 2 + 1);
        }
        else
        {
          /*nothing to do*/
        }
    } while(x <= 0);

    return;
}






void ssd1306_FillCircle(uint8_t x0,uint8_t y0,uint8_t r,SSD1306_COLOR color)//写画实心圆心(x0,y0),半径r
{	
	uint32_t i;
	uint32_t imax = ((uint32_t)r*707)/1000+1;
	uint32_t sqmax = (uint32_t)r*(uint32_t)r+(uint32_t)r/2;
	uint32_t x=r;
	ssd1306_DrawHLine(x0-r,y0,2*r,color);
	for (i=1;i<=imax;i++) 
	{
		if ((i*i+x*x)>sqmax) 
		{
			// draw lines from outside  
			if (x>imax) 
			{
				ssd1306_DrawHLine (x0-i+1,y0+x,2*(i-1),color);
				ssd1306_DrawHLine (x0-i+1,y0-x,2*(i-1),color);
			}
			x--;
		}
		// draw lines from inside (center)  
		ssd1306_DrawHLine(x0-x,y0+i,2*x,color);
		ssd1306_DrawHLine(x0-x,y0-i,2*x,color);
	}
}





//Draw rectangle
void ssd1306_DrawRectangle(uint8_t x1, uint8_t y1, int w, int h , SSD1306_COLOR color) {
  int x2 = x1+w;
  int y2 = y1+h;
  ssd1306_DrawLine(x1,y1,x2,y1,color);
  ssd1306_DrawLine(x2,y1,x2,y2,color);
  ssd1306_DrawLine(x2,y2,x1,y2,color);
  ssd1306_DrawLine(x1,y2,x1,y1,color);
  return;
}



void ssd1306_FillRectangle(uint8_t x0, uint8_t y0, int w, int h, SSD1306_COLOR color) {
	int cnt = abs(w);
	int y1 = y0 + h;

	
	do{
		if(w>0){
			ssd1306_DrawLine(x0+cnt,y0,x0+cnt,y1,color);
		}else{
			ssd1306_DrawLine(x0-cnt,y0,x0-cnt,y1,color);
		}
	}while(cnt--);
	return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//画圆角矩形
void ssd1306_DrawRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r,SSD1306_COLOR color)
{
	//画出边缘 因为边缘是直线 所以专用高效率函数
	ssd1306_DrawHLine(x+r, y, w-2*r,color); 		// Top
	ssd1306_DrawHLine(x+r, y+h-1, w-2*r,color); 	// Bottom
	ssd1306_DrawVLine(x, y+r, h-2*r,color); 		// Left
	ssd1306_DrawVLine(x+w-1, y+r, h-2*r,color); 	// Right
	//画出四个圆角
	ssd1306_DrawCircleHelper(x+r, y+r, r, 1,color);
	ssd1306_DrawCircleHelper(x+w-r-1, y+r, r, 2 ,color);
	ssd1306_DrawCircleHelper(x+w-r-1, y+h-r-1, r, 4 ,color);
	ssd1306_DrawCircleHelper(x+r, y+h-r-1, r, 8 ,color);
}





//画实心圆角矩形
void ssd1306_DrawfillRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r,SSD1306_COLOR color)
{
  
  //画实心矩形
  ssd1306_FillRectangle(x+r, y, x+w-2*r, y+h,color);
  //再填充左右两边
  ssd1306_DrawFillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1,color);	//右上角的圆心
  ssd1306_DrawFillCircleHelper(x+r, y+r, r, 2, h-2*r-1,color);		//左下角的圆心
}












/* 画椭圆 */
void ssd1306_DrawEllipse(int xCenter,int yCenter,int Rx,int Ry,SSD1306_COLOR color)
{
	int Rx2=Rx*Rx;
	int Ry2=Ry*Ry;
	int twoRx2=2*Rx2;
	int twoRy2=2*Ry2;
	int p;
	int x=0;
	int y=Ry;
	int px = 0;
	int py = twoRx2*y;
	
	//椭圆最下面的点
	ssd1306_DrawPixel(xCenter+x,yCenter+y,color);//因为此时x=0 俩个点为同一个 原作这样写的 那就这样吧
	ssd1306_DrawPixel(xCenter-x,yCenter+y,color);//椭圆最上面的点
	ssd1306_DrawPixel(xCenter+x,yCenter-y,color);
	ssd1306_DrawPixel(xCenter-x,yCenter-y,color);
	
	//Region?1 画出上下的线条 说实话我也没看懂了 算法大佬
	p=(int)(Ry2-Rx2*Ry+0.25*Rx2);
	while(px<py)
	{
		x++;
		px+=twoRy2;
		if(p<0)
			p+=Ry2+px;
		else
		{
			y--;
			py-=twoRx2;
			p+=Ry2+px-py;
		}
		ssd1306_DrawPixel(xCenter+x,yCenter+y,color);
		ssd1306_DrawPixel(xCenter-x,yCenter+y,color);
		ssd1306_DrawPixel(xCenter+x,yCenter-y,color);
		ssd1306_DrawPixel(xCenter-x,yCenter-y,color);
	}
	
	//Region?2
	p=(int)(Ry2*(x+0.5)*(x+0.5)+Rx2*(y-1)*(y-1)-Rx2*Ry2);
	while(y>0)
	{
		y--;
		py-=twoRx2;
		if(p>0)
			p+=Rx2-py;
		else
		{
			x++;
			px+=twoRy2;
			p+=Rx2-py+px;
		}
		ssd1306_DrawPixel(xCenter+x,yCenter+y,color);
		ssd1306_DrawPixel(xCenter-x,yCenter+y,color);
		ssd1306_DrawPixel(xCenter+x,yCenter-y,color);
		ssd1306_DrawPixel(xCenter-x,yCenter-y,color);
	}
}




//填充一个椭圆 参数同上
void ssd1306_DrawFillEllipse(int x0, int y0,int rx,int ry,SSD1306_COLOR color)
{
	int x, y;
	int xchg, ychg;
	int err;
	int rxrx2;
	int ryry2;
	int stopx, stopy;

	rxrx2 = rx;
	rxrx2 *= rx;
	rxrx2 *= 2;

	ryry2 = ry;
	ryry2 *= ry;
	ryry2 *= 2;

	x = rx;
	y = 0;

	xchg = 1;
	xchg -= rx;
	xchg -= rx;
	xchg *= ry;
	xchg *= ry;

	ychg = rx;
	ychg *= rx;

	err = 0;

	stopx = ryry2;
	stopx *= rx;
	stopy = 0;

	while( stopx >= stopy )
	{
		ssd1306_DrawVLine( x0+x, y0-y, y+1,color);
		ssd1306_DrawVLine( x0-x, y0-y, y+1,color);
		ssd1306_DrawVLine( x0+x, y0, y+1,color);
		ssd1306_DrawVLine( x0-x, y0, y+1,color);
		y++;
		stopy += rxrx2;
		err += ychg;
		ychg += rxrx2;
		if ( 2*err+xchg > 0 )
		{
			x--;
			stopx -= ryry2;
			err += xchg;
			xchg += ryry2;      
		}
	}

	x = 0;
	y = ry;

	xchg = ry;
	xchg *= ry;

	ychg = 1;
	ychg -= ry;
	ychg -= ry;
	ychg *= rx;
	ychg *= rx;

	err = 0;
	stopx = 0;
	stopy = rxrx2;
	stopy *= ry;

	while( stopx <= stopy )
	{
		ssd1306_DrawVLine( x0+x, y0-y, y+1,color);
		ssd1306_DrawVLine( x0-x, y0-y, y+1,color);
		ssd1306_DrawVLine( x0+x, y0, y+1,color);
		ssd1306_DrawVLine( x0-x, y0, y+1,color);
		x++;
		stopx += ryry2;
		err += xchg;
		xchg += ryry2;
		if (2*err+ychg>0)
		{
			y--;
			stopy -= rxrx2;
			err += ychg;
			ychg += rxrx2;
		}
	}
}







//功能:绘制一个矩形内切椭圆
//x0,y0:矩形左上角坐标
//x1,y1:矩形右下角坐标
void ssd1306_DrawEllipseRect( int x0, int y0, int x1, int y1,SSD1306_COLOR color)
{
	int a = abs(x1 - x0);
	int b = abs(y1 - y0);	//get diameters
	int b1 = b&1;
	long dx = 4*(1-a)*b*b;
	long dy = 4*(b1+1)*a*a;
	long err = dx+dy+b1*a*a;
	long e2;
	if (x0 > x1) { x0 = x1; x1 += a; }
	if (y0 > y1) { y0 = y1; } 
	y0 += (b+1)/2;
	y1 = y0-b1;
	a *= 8*a;
	b1 = 8*b*b;
	do {
		ssd1306_DrawPixel( x1, y0,color);
		ssd1306_DrawPixel( x0, y0,color);
		ssd1306_DrawPixel( x0, y1,color);
		ssd1306_DrawPixel( x1, y1,color);
		e2 = 2*err;
		if (e2 >= dx) {
			x0++;
			x1--;
			err += dx += b1;
		}
		if (e2 <= dy) {
			y0++;
			y1--;
			err += dy += a;
		}
	} while (x0 <= x1);
	while (y0-y1 < b) {
		ssd1306_DrawPixel( x0-1, y0 ,color);
		ssd1306_DrawPixel( x1+1, y0++,color);
		ssd1306_DrawPixel( x0-1, y1,color);
		ssd1306_DrawPixel( x1+1, y1--,color);
	}
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//画三角形
void ssd1306_DrawTriangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,SSD1306_COLOR color)
{
	//很简单  就是画3条任意线
	ssd1306_DrawLine(x0, y0, x1, y1,color);
	ssd1306_DrawLine(x1, y1, x2, y2,color);
	ssd1306_DrawLine(x2, y2, x0, y0,color);
}







//填充三角形
void ssd1306_DrawFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2,SSD1306_COLOR color)
{
	
	int a, b, y, last;
	int dx01, dy01,dx02,dy02,dx12,dy12,sa = 0,sb = 0;
	

	if (y0 > y1)
	{
		SWAP(y0, y1); SWAP(x0, x1);
	}
	if (y1 > y2)
	{
		SWAP(y2, y1); SWAP(x2, x1);
	}
	if (y0 > y1)
	{
		SWAP(y0, y1); SWAP(x0, x1);
	}
	if(y0 == y2)
	{
		a = b = x0;
		if(x1 < a)
		{
			a = x1;
		}
		else if(x1 > b)
		{
			b = x1;
		}
		if(x2 < a)
		{
			a = x2;
		}
		else if(x2 > b)
		{
			b = x2;
		}
		ssd1306_DrawHLine(a, y0, b-a+1,color);
		return;
	}
	dx01 = x1 - x0,
	dy01 = y1 - y0,
	dx02 = x2 - x0,
	dy02 = y2 - y0,
	dx12 = x2 - x1,
	dy12 = y2 - y1,
	sa = 0,
	sb = 0;
	if (y1 == y2)
	{
		last = y1;   // Include y1 scanline
	}
	else
	{
		last = y1-1; // Skip it
	}

	for(y = y0; y <= last; y++)
	{
		a   = x0 + sa / dy01;
		b   = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;

		if(a > b)
		{
			SWAP(a,b);
		}
		ssd1306_DrawHLine(a, y, b-a+1,color);
	}
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y <= y2; y++)
	{
		a   = x1 + sa / dy12;
		b   = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		if(a > b)
		{
			SWAP(a,b);
		}
		ssd1306_DrawHLine(a, y, b-a+1,color);
	}

}



/* 画指针 */
void ssd1306_DrawLineOfArc(int x0, int y0, uint8_t radius, uint16_t angle,SSD1306_COLOR color) { 
#if 1
	float approx_degree; 
	 
	uint8_t xp1; 
	 
	uint8_t yp1; 
	 
	uint32_t count = 0; 
	 
	float rad; 
	 
	count = (ssd1306_NormalizeTo0_360(angle)); 
	 
	approx_degree = 1; 
	 
	rad = ssd1306_DegToRad(count*approx_degree); 
	 
	xp1 = x0 - (int8_t)(cos(rad)*radius); 
	 
	yp1 = y0 - (int8_t)(sin(rad)*radius); 
	 
	ssd1306_DrawLine(x0, y0, xp1, yp1, color); 
 #endif

} 



/* 画刻度 */
void ssd1306_DrawLineOfKedu(uint8_t x, uint8_t y, uint8_t radius,uint8_t len, uint16_t angle,SSD1306_COLOR color) 
{ 
	float approx_degree; 
	uint8_t xp1,xp2; 
	uint8_t yp1,yp2; 
	uint32_t count = 0; 
	float rad; 
	count = (ssd1306_NormalizeTo0_360(angle)); 
	approx_degree = 1; 
	rad = ssd1306_DegToRad(count*approx_degree); 
	xp1 = x - (int8_t)(cos(rad)*radius); 
	yp1 = y - (int8_t)(sin(rad)*radius); 
	xp2 = x - (int8_t)(cos(rad)*(radius-len));//刻度线的长度为4 
	yp2 = y - (int8_t)(sin(rad)*(radius-len)); 
	ssd1306_DrawLine(xp1, yp1, xp2, yp2, color); 
} 














void ssd1306_DrawBitmap(int32_t x, int32_t y, int32_t width, int32_t height, const uint8_t *image,uint32_t size,SSD1306_COLOR color)
{
    if(width==0 && height==0 || !image) return;
    uint8_t _x = x, _y = y;
	uint32_t image_cnt = 0;
    for(uint8_t j=0; j<height; j++){
        if(_y > 63) break;
        for(uint8_t i=0; i<width/8; i++)
        {
            uint8_t data = *image;
			if(color==Black)
		    {
		        data = ~data;
		    }
            for(uint8_t k=0; k<8; k++)
            {
                if(_x>127) break;
                if(data & 0x80)
                    ssd1306_DrawPixel(_x,_y,White);
                else
                    ssd1306_DrawPixel(_x,_y,Black);
                data = data << 1;
                _x++;
            }
            image++;
			image_cnt ++;
            if(!image || (image_cnt>size)) return;
        }
        if(width%8){
            uint8_t data = *image;
			if(color==Black)
		    {
		        data = ~data;
		    }
            for(uint8_t i=0; i<width%8; i++)
            {
                if(_x>127) break;
                if(data & 0x80)
                    ssd1306_DrawPixel(_x,_y,White);
                else
                    ssd1306_DrawPixel(_x,_y,Black);
                data = data << 1;
                _x++;
            }
            image++;
            if(!image || (image_cnt>size)) return;
        }
        _y++;_x = x;
    }
}





void ssd1306_DrawRegion(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t* data, uint32_t size, uint32_t stride,uint8_t mode)
{
    if (x + w > SSD1306_WIDTH || y + h > SSD1306_HEIGHT || w * h == 0) {
        return;
    }
    w = (w <= SSD1306_WIDTH ? w : SSD1306_WIDTH);
    h = (h <= SSD1306_HEIGHT ? h : SSD1306_HEIGHT);
    stride = (stride == 0 ? w : stride);

    uint8_t rows = size * 8 / stride;
    for (uint8_t i = 0; i < rows; i++) {
        uint32_t base = i * stride / 8;
        for (uint8_t j = 0; j < w; j++) {
            uint32_t idx = base + (j / 8);
            uint8_t byte = idx < size ? data[idx] : 0;
            uint8_t bit  = byte & (0x80 >> (j % 8));
			bit = mode? bit: !bit;
            ssd1306_DrawPixel(x + j, y + i, bit ? White : Black);
        }
    }
}


void ssd1306_SetContrast(const uint8_t value) {
    const uint8_t kSetContrastControlRegister = 0x81;
    ssd1306_WriteCommand(kSetContrastControlRegister);
    ssd1306_WriteCommand(value);
}


void ssd1306_SetDisplayOn(const uint8_t on) {
    uint8_t value;
    if (on) {
        value = 0xAF;   // Display on
        SSD1306.DisplayOn = 1;
    } else {
        value = 0xAE;   // Display off
        SSD1306.DisplayOn = 0;
    }
    ssd1306_WriteCommand(value);
}


uint8_t ssd1306_GetDisplayOn() {
    return SSD1306.DisplayOn;
}


#endif



