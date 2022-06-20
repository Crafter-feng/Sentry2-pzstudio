/*
 * Copyright (c) 2020, HiHope Community.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef OLED_SSD1306_H
#define OLED_SSD1306_H

#include <stdint.h>
#if BUILD_BOARD == DASHIXIONG_BOARD
#include "oled_ssd1306_fonts.h"



#define OLED_PI 3.14159265

// SSD1306 OLED height in pixels
#ifndef SSD1306_HEIGHT
#define SSD1306_HEIGHT          64
#endif

// SSD1306 width in pixels
#ifndef SSD1306_WIDTH
#define SSD1306_WIDTH           128
#endif

// some LEDs don't display anything in first two columns
// #define SSD1306_WIDTH           130

#ifndef SSD1306_BUFFER_SIZE
#define SSD1306_BUFFER_SIZE   SSD1306_WIDTH * SSD1306_HEIGHT / 8
#endif

// Enumeration for screen colors
typedef enum {
    Black = 0x00, // Black color, no pixel
    White = 0x01  // Pixel is set. Color depends on OLED
} SSD1306_COLOR;

typedef enum {
    SSD1306_OK = 0x00,
    SSD1306_ERR = 0x01  // Generic error.
} SSD1306_Error_t;

// Struct to store transformations
typedef struct {
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t Inverted;
    uint8_t Initialized;
    uint8_t DisplayOn;
	uint16_t head_index;
	uint16_t data_len;
	uint8_t *data;
	uint8_t *buf;
} SSD1306_t;
typedef struct {
    uint8_t x;
    uint8_t y;
} SSD1306_VERTEX;




#define SWAP(x,y)   do{typeof(x) t;t=x;x=y;y=t;}while(0)


uint32_t OledInit(int8_t i2c_id, uint8_t i2c_addr,uint32_t baudrate);
uint32_t OledDeinit(void);
void ssd1306_Fill(SSD1306_COLOR color);
void ssd1306_SetCursor(uint8_t x, uint8_t y);
void ssd1306_UpdateScreen(void);

//char ssd1306_DrawChar(char ch, FontDef Font, SSD1306_COLOR color);
//char ssd1306_DrawString(char* str, FontDef Font, SSD1306_COLOR color);
void ssd1306_DrawChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode,SSD1306_COLOR color);
void ssd1306_Show_Str(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t*str,uint8_t size,uint8_t mode,SSD1306_COLOR color);
void ssd1306_Show_Str_Line(uint8_t line, uint8_t*str,uint8_t size,SSD1306_COLOR color);
void ssd1306_fill_screen_line(int line,SSD1306_COLOR color);

void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
void ssd1306_DrawHLine(uint8_t x1, uint8_t y1, uint8_t w,SSD1306_COLOR color);
void ssd1306_DrawVLine(uint8_t x1, uint8_t y1, uint8_t h,SSD1306_COLOR color);

void ssd1306_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
void ssd1306_DrawPolyline(const SSD1306_VERTEX *par_vertex, uint16_t par_size, SSD1306_COLOR color);
void ssd1306_DrawRectangle(uint8_t x1, uint8_t y1, int w, int h , SSD1306_COLOR color);
void ssd1306_FillRectangle(uint8_t x0, uint8_t y0, int w, int h, SSD1306_COLOR color);
void ssd1306_DrawArc(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR color);
//void ssd1306_DrawArc(int x0, int y0, int rx, int ry, int a0, int a1);

void ssd1306_DrawCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername,SSD1306_COLOR color);
void ssd1306_DrawFillCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername, int delta,SSD1306_COLOR color);
void ssd1306_DrawCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r, SSD1306_COLOR color);
void ssd1306_FillCircle(uint8_t x1,uint8_t y1,uint8_t r,SSD1306_COLOR color);
void ssd1306_DrawRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r,SSD1306_COLOR color);
void ssd1306_DrawfillRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r,SSD1306_COLOR color);
void ssd1306_DrawEllipse(int xCenter,int yCenter,int Rx,int Ry,SSD1306_COLOR color);
void ssd1306_DrawFillEllipse(int x0, int y0,int rx,int ry,SSD1306_COLOR color);
void ssd1306_DrawEllipseRect( int x0, int y0, int x1, int y1,SSD1306_COLOR color);
void ssd1306_DrawTriangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,SSD1306_COLOR color);
void ssd1306_DrawFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2,SSD1306_COLOR color);
void ssd1306_DrawLineOfArc(int x, int y, uint8_t radius, uint16_t angle,SSD1306_COLOR color);
void ssd1306_DrawLineOfKedu(uint8_t x, uint8_t y, uint8_t radius,uint8_t len, uint16_t angle,SSD1306_COLOR color) ;

//void ssd1306_DrawBitmap(const uint8_t* bitmap, uint32_t size);
void ssd1306_DrawBitmap(int32_t x, int32_t y, int32_t width, int32_t height, const uint8_t *image,uint32_t size,SSD1306_COLOR color);


void ssd1306_DrawRegion(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t* data, uint32_t size, uint32_t stride,uint8_t mode);

/**
 * @brief Sets the contrast of the display.
 * @param[in] value contrast to set.
 * @note Contrast increases as the value increases.
 * @note RESET = 7Fh.
 */
void ssd1306_SetContrast(const uint8_t value);
/**
 * @brief Set Display ON/OFF.
 * @param[in] on 0 for OFF, any for ON.
 */
void ssd1306_SetDisplayOn(const uint8_t on);
/**
 * @brief Reads DisplayOn state.
 * @return  0: OFF.
 *          1: ON.
 */
uint8_t ssd1306_GetDisplayOn(void);

#endif
#endif // OLED_SSD1306_H
