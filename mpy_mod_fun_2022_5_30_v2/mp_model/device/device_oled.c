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
#if BUILD_BOARD == DASHIXIONG_BOARD
#include "moddevice.h"
#include "modmachine.h"
#include "oled_ssd1306.h"

static int8_t new_class_flag = 0;


typedef struct _device_oled_obj_t {
    mp_obj_base_t base;
	uint8_t id;
	uint8_t dev_addr;
	uint32_t baudrate;
} device_oled_obj_t;




MP_STATIC int device_oled_init(device_oled_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
	int ret = 0;
	enum {ARG_baudrate,ARG_addr};
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_baudrate, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_addr, MP_ARG_INT, {.u_int = 0} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);
	if(args[ARG_baudrate].u_int != 0){
		/* 重新修改波特率 */
		self->baudrate = args[ARG_baudrate].u_int;
		IoTI2cSetBaudrate(self->baudrate);
	}
	if(args[ARG_addr].u_int != 0){
		/* 重新修改设备地址 */
		self->dev_addr = args[ARG_addr].u_int;
		set_oled_i2c_arg(self->id,self->dev_addr);
	}
	/* 初始化i2c */
	if(new_class_flag == 0){
		ret = OledInit(self->id, self->dev_addr,self->baudrate);
		if(ret==0){
			new_class_flag = 0;
		}
	}
	return ret;
}





/******************************************************************************/
// MicroPython bindings for machine API
MP_STATIC void device_oled_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    device_oled_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "OLED(i2c_id=%u, addr=%u, baud=%u)",self->id, self->dev_addr, self->baudrate);
}







mp_obj_t device_oled_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    mp_arg_check_num(n_args, n_kw, 1, 2, true);
    mp_int_t addr = mp_obj_get_int(all_args[0]);
	device_oled_obj_t *self = m_new_obj(device_oled_obj_t);
	if(self == NULL){
		mp_raise_msg(&mp_type_RuntimeError,MP_ERROR_TEXT("micropython run out of memory"));
	}
	self->base.type = &device_oled_type;
	self->id = 0;
	self->dev_addr = addr;
	self->baudrate = 400000;
	mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, all_args + n_args);    
	int ret = device_oled_init(self, n_args - 1, all_args + 1, &kw_args);
	if(ret==0){
    	return MP_OBJ_FROM_PTR(self);
	}else{
		return mp_const_none;
	}
}







MP_STATIC mp_obj_t mp_device_oled_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    int ret = device_oled_init(args[0], n_args - 1, args + 1, kw_args);
	if(ret == 0){
		return mp_const_true;
	}else{
		return mp_const_false;
	}
}
MP_DEFINE_CONST_FUN_OBJ_KW(mp_device_oled_init_obj, 1, mp_device_oled_init);




mp_obj_t mp_oled_showstr(size_t n_args, const mp_obj_t *args) {
	
	
	//FontDef *Font_type = &Font_7x10;
    char *c = mp_obj_str_get_str(args[1]);
	int x = mp_obj_get_int(args[2]);
    int y = mp_obj_get_int(args[3]);
	
	int color = mp_obj_get_int(args[4]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}

	ssd1306_Show_Str(x,y,SSD1306_WIDTH,SSD1306_HEIGHT,c,12,0,color);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_showstr_obj, 5, 6, mp_oled_showstr);






mp_obj_t mp_oled_showstr_line(size_t n_args, const mp_obj_t *args) {

    char *c = mp_obj_str_get_str(args[1]);
	int line = mp_obj_get_int(args[2]);
    
	
	int color = mp_obj_get_int(args[3]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_Show_Str_Line(line,(uint8_t*)c,12,color);
    return mp_const_none;
}

MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_showstr_line_obj, 4, 4, mp_oled_showstr_line);

mp_obj_t mp_oled_fill_screen_line(mp_obj_t self_in,mp_obj_t index,mp_obj_t color) {
    int i = mp_obj_get_int(index);
	int c = mp_obj_get_int(color);
	if(c!=0){
		c = 1;
	}
    ssd1306_fill_screen_line(i,c);
    return mp_const_none;
}


MP_DEFINE_CONST_FUN_OBJ_3(mp_oled_fill_screen_line_obj, mp_oled_fill_screen_line);




mp_obj_t mp_oled_clear(mp_obj_t self_in) {
    ssd1306_Fill(Black);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_oled_clear_obj, mp_oled_clear);





mp_obj_t mp_oled_fill_screen(mp_obj_t self_in,mp_obj_t index) {
    int i = mp_obj_get_int(index);
	if(i!=0){
		i = 1;
	}
    ssd1306_Fill(i);
    return mp_const_none;
}

MP_DEFINE_CONST_FUN_OBJ_2(mp_oled_fill_screen_obj, mp_oled_fill_screen);


mp_obj_t mp_oled_flush(mp_obj_t self_in) {
    (void*)self_in;
	ssd1306_UpdateScreen();
    return mp_const_none;
}

MP_DEFINE_CONST_FUN_OBJ_1(mp_oled_flush_obj, mp_oled_flush);




#if 0

char ssd1306_DrawChar(char ch, FontDef Font, SSD1306_COLOR color);
char ssd1306_DrawString(char* str, FontDef Font, SSD1306_COLOR color);

void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
void ssd1306_DrawHLine(uint8_t x1, uint8_t y1, uint8_t w,SSD1306_COLOR color);
void ssd1306_DrawVLine(uint8_t x1, uint8_t y1, uint8_t h,SSD1306_COLOR color);

void ssd1306_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
void ssd1306_DrawPolyline(const SSD1306_VERTEX *par_vertex, uint16_t par_size, SSD1306_COLOR color);
void ssd1306_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
void ssd1306_FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color) ;
void ssd1306_DrawArc(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR color);
void ssd1306_DrawCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername,SSD1306_COLOR color);
void ssd1306_DrawFillCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername, int delta,SSD1306_COLOR color);
void ssd1306_DrawCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r, SSD1306_COLOR color);
void ssd1306_FillCircle(uint8_t x1,uint8_t y1,uint8_t r,SSD1306_COLOR color);




#endif


mp_obj_t mp_oled_pixel(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x = mp_obj_get_int(args[1]);
    int y = mp_obj_get_int(args[2]);
	
	int color = mp_obj_get_int(args[3]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawPixel(x,y,color);
    return mp_const_none;
}

MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_pixel_obj, 4, 4, mp_oled_pixel);





mp_obj_t mp_oled_draw_hline(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x1 = mp_obj_get_int(args[1]);
    int y1 = mp_obj_get_int(args[2]);
	int w = mp_obj_get_int(args[3]);
	int color = mp_obj_get_int(args[4]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawHLine(x1,y1,w,color);
    return mp_const_none;
}

MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_draw_hline_obj, 5, 5, mp_oled_draw_hline);



mp_obj_t mp_oled_draw_vline(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x1 = mp_obj_get_int(args[1]);
    int y1 = mp_obj_get_int(args[2]);
	int h = mp_obj_get_int(args[3]);
	int color = mp_obj_get_int(args[4]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawVLine(x1,y1,h,color);
    return mp_const_none;
}

MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_draw_vline_obj, 5, 5, mp_oled_draw_vline);



mp_obj_t mp_oled_draw_line(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x1 = mp_obj_get_int(args[1]);
    int y1 = mp_obj_get_int(args[2]);
	int x2 = mp_obj_get_int(args[3]);
    int y2 = mp_obj_get_int(args[4]);
	int color = mp_obj_get_int(args[5]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawLine(x1,y1,x2,y2,color);
    return mp_const_none;
}

MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_draw_line_obj, 6, 6, mp_oled_draw_line);








mp_obj_t mp_oled_draw_arc(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x1 = mp_obj_get_int(args[1]);
    int y1 = mp_obj_get_int(args[2]);
	int radius = mp_obj_get_int(args[3]);
    int start_angle = mp_obj_get_int(args[4]);
	int sweep = mp_obj_get_int(args[5]);
	int color = mp_obj_get_int(args[6]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawArc(x1,y1,radius,start_angle,sweep,color);
    return mp_const_none;
}

MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_draw_arc_obj, 7, 7, mp_oled_draw_arc);





#if 0
mp_obj_t mp_oled_draw_circle_helper(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x1 = mp_obj_get_int(args[1]);
    int y1 = mp_obj_get_int(args[2]);
	int radius = mp_obj_get_int(args[3]);
	unsigned char  cornername = mp_obj_get_int_truncated(args[4]);
	int color = mp_obj_get_int(args[5]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawCircleHelper(x1,y1,radius,cornername,color);
    return mp_const_none;
}

MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_draw_circle_helper_obj, 6, 6, mp_oled_draw_circle_helper);



//void ssd1306_DrawFillCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername, int delta,SSD1306_COLOR color);



mp_obj_t mp_oled_fill_circle_helper(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x1 = mp_obj_get_int(args[1]);
    int y1 = mp_obj_get_int(args[2]);
	int radius = mp_obj_get_int(args[3]);
	unsigned char  cornername = mp_obj_get_int_truncated(args[4]);
	int delta = mp_obj_get_int(args[5]);
	int color = mp_obj_get_int(args[6]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawFillCircleHelper(x1,y1,radius,cornername,delta,color);
    return mp_const_none;
}

MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_fill_circle_helper_obj, 7, 7, mp_oled_fill_circle_helper);
#endif


mp_obj_t mp_oled_draw_circle(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x1 = mp_obj_get_int(args[1]);
    int y1 = mp_obj_get_int(args[2]);
	int radius = mp_obj_get_int(args[3]);
	int color = mp_obj_get_int(args[4]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawCircle(x1,y1,radius,color);
    return mp_const_none;
}

MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_draw_circle_obj, 5, 5, mp_oled_draw_circle);





mp_obj_t mp_oled_fill_circle(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x1 = mp_obj_get_int(args[1]);
	int y1 = mp_obj_get_int(args[2]);
	int radius = mp_obj_get_int(args[3]);
	int color = mp_obj_get_int(args[4]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_FillCircle(x1,y1,radius,color);
	return mp_const_none;
}

MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_fill_circle_obj, 5, 5, mp_oled_fill_circle);





mp_obj_t mp_oled_draw_rectangle(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x1 = mp_obj_get_int(args[1]);
    int y1 = mp_obj_get_int(args[2]);
	int x2 = mp_obj_get_int(args[3]);
	int y2 = mp_obj_get_int(args[4]);
	int color = mp_obj_get_int(args[5]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawRectangle(x1,y1,x2,y2,color);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_draw_rectangle_obj, 6, 6, mp_oled_draw_rectangle);


//void ssd1306_FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color) ;
mp_obj_t mp_oled_fill_rectangle(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x1 = mp_obj_get_int(args[1]);
    int y1 = mp_obj_get_int(args[2]);
	int x2 = mp_obj_get_int(args[3]);
	int y2 = mp_obj_get_int(args[4]);
	int color = mp_obj_get_int(args[5]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_FillRectangle(x1,y1,x2,y2,color);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_fill_rectangle_obj, 6, 6, mp_oled_fill_rectangle);



//void ssd1306_DrawRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r,SSD1306_COLOR color);
mp_obj_t mp_oled_draw_round_rectangle(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x1 = mp_obj_get_int(args[1]);
    int y1 = mp_obj_get_int(args[2]);
	int w = mp_obj_get_int(args[3]);
	int h = mp_obj_get_int(args[4]);
	int r = mp_obj_get_int(args[5]);
	int color = mp_obj_get_int(args[6]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawRoundRect(x1,y1,w,h,r,color);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_draw_round_rectangle_obj, 7, 7, mp_oled_draw_round_rectangle);




//void ssd1306_DrawfillRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r,SSD1306_COLOR color);
mp_obj_t mp_oled_fill_round_rectangle(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x1 = mp_obj_get_int(args[1]);
    int y1 = mp_obj_get_int(args[2]);
	int w = mp_obj_get_int(args[3]);
	int h = mp_obj_get_int(args[4]);
	int r = mp_obj_get_int(args[5]);
	int color = mp_obj_get_int(args[6]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawfillRoundRect(x1,y1,w,h,r,color);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_fill_round_rectangle_obj, 7, 7, mp_oled_fill_round_rectangle);



/* 画椭圆 */
//void ssd1306_DrawEllipse(int xCenter,int yCenter,int Rx,int Ry,SSD1306_COLOR color);
mp_obj_t mp_oled_draw_ellipse(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int xCenter = mp_obj_get_int(args[1]);
    int yCenter = mp_obj_get_int(args[2]);
	int Rx = mp_obj_get_int(args[3]);
	int Ry = mp_obj_get_int(args[4]);
	int color = mp_obj_get_int(args[5]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawEllipse(xCenter,yCenter,Rx,Ry,color);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_draw_ellipse_obj, 6, 6, mp_oled_draw_ellipse);


/* 填充椭圆 */
//void ssd1306_DrawFillEllipse(int x0, int y0,int rx,int ry,SSD1306_COLOR color);
mp_obj_t mp_oled_fill_ellipse(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int xCenter = mp_obj_get_int(args[1]);
    int yCenter = mp_obj_get_int(args[2]);
	int Rx = mp_obj_get_int(args[3]);
	int Ry = mp_obj_get_int(args[4]);
	int color = mp_obj_get_int(args[5]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawFillEllipse(xCenter,yCenter,Rx,Ry,color);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_fill_ellipse_obj, 6, 6, mp_oled_fill_ellipse);

/* 画矩形内切椭圆 */
//void ssd1306_DrawEllipseRect( int x0, int y0, int x1, int y1,SSD1306_COLOR color);
mp_obj_t mp_oled_draw_ellipse_rect(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x1 = mp_obj_get_int(args[1]);
    int y1 = mp_obj_get_int(args[2]);
	int x2 = mp_obj_get_int(args[3]);
	int y2 = mp_obj_get_int(args[4]);
	int color = mp_obj_get_int(args[5]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawEllipseRect(x1,y1,x2,y2,color);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_draw_ellipse_rect_obj, 6, 6, mp_oled_draw_ellipse_rect);

/* 画三角形 */
//void ssd1306_DrawTriangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2,SSD1306_COLOR color);
mp_obj_t mp_oled_draw_triangle(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x1 = mp_obj_get_int(args[1]);
    int y1 = mp_obj_get_int(args[2]);
	int x2 = mp_obj_get_int(args[3]);
	int y2 = mp_obj_get_int(args[4]);
	int x3 = mp_obj_get_int(args[5]);
	int y3 = mp_obj_get_int(args[6]);
	int color = mp_obj_get_int(args[7]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawTriangle(x1,y1,x2,y2,x3,y3,color);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_draw_triangle_obj, 8, 8, mp_oled_draw_triangle);

/* 填充三角形 */
//void ssd1306_DrawFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2,SSD1306_COLOR color);
mp_obj_t mp_oled_fill_triangle(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x1 = mp_obj_get_int(args[1]);
    int y1 = mp_obj_get_int(args[2]);
	int x2 = mp_obj_get_int(args[3]);
	int y2 = mp_obj_get_int(args[4]);
	int x3 = mp_obj_get_int(args[5]);
	int y3 = mp_obj_get_int(args[6]);
	int color = mp_obj_get_int(args[7]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawFillTriangle(x1,y1,x2,y2,x3,y3,color);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_fill_triangle_obj, 8, 8, mp_oled_fill_triangle);


/* 画指针 */
//void ssd1306_DrawLineOfArc(uint8_t x, uint8_t y, uint8_t radius, uint16_t angle,SSD1306_COLOR color);

mp_obj_t mp_oled_draw_line_of_arc(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x = mp_obj_get_int(args[1]);
    int y = mp_obj_get_int(args[2]);
	int radius = mp_obj_get_int(args[3]);
	int angle = mp_obj_get_int(args[4]);
	int color = mp_obj_get_int(args[5]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawLineOfArc(x,y,radius,angle,color);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_draw_line_of_arc_obj, 6, 6, mp_oled_draw_line_of_arc);



/* 画刻度 */
//void ssd1306_DrawLineOfKedu(uint8_t x, uint8_t y, uint8_t radius, uint16_t angle,SSD1306_COLOR color) ;
mp_obj_t mp_oled_draw_line_of_kedu(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x = mp_obj_get_int(args[1]);
    int y = mp_obj_get_int(args[2]);
	int radius = mp_obj_get_int(args[3]);
	int len = mp_obj_get_int(args[4]);
	int angle = mp_obj_get_int(args[5]);
	int color = mp_obj_get_int(args[6]);
	if(color == Black){
		color = Black;
	}else{
		color = White;
	}
	ssd1306_DrawLineOfKedu(x,y,radius,len,angle,color);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_draw_line_of_kedu_obj, 7, 7, mp_oled_draw_line_of_kedu);

//void ssd1306_DrawBitmap(int32_t x, int32_t y, int32_t width, int32_t height, const uint8_t *image,uint32_t size,SSD1306_COLOR color);

mp_obj_t mp_oled_draw_bit_map(size_t n_args, const mp_obj_t *args) {
	n_args = n_args;
	int x = mp_obj_get_int(args[1]);
    int y = mp_obj_get_int(args[2]);
	
	
	int w = mp_obj_get_int(args[3]);
	int h = mp_obj_get_int(args[4]);
	int mode = mp_obj_get_int(args[5]);
	
	mp_buffer_info_t bitmap_buf;
	mp_get_buffer_raise(args[6], &bitmap_buf, MP_BUFFER_READ);
	
	if(bitmap_buf.len>0){
		ssd1306_DrawBitmap(x,y,w,h,bitmap_buf.buf,bitmap_buf.len,mode);
	}
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_draw_bit_map_obj, 7, 7, mp_oled_draw_bit_map);




#if 0

mp_oled_pixel_obj
mp_oled_draw_hline_obj
mp_oled_draw_vline_obj
mp_oled_draw_line_obj
mp_oled_draw_arc_obj
mp_oled_draw_circle_helper_obj
mp_oled_fill_circle_helper_obj
mp_oled_draw_circle_obj
mp_oled_fill_circle_obj
mp_oled_draw_rectangle_obj
mp_oled_fill_rectangle_obj
mp_oled_draw_round_rectangle_obj
mp_oled_fill_round_rectangle_obj
mp_oled_draw_ellipse_obj
mp_oled_fill_ellipse_obj
mp_oled_draw_ellipse_rect_obj

mp_oled_draw_triangle_obj
mp_oled_fill_triangle_obj

mp_oled_draw_line_of_arc_obj
mp_oled_draw_line_of_kedu_obj
mp_oled_draw_bit_map_obj

#endif


//MP_DEFINE_CONST_FUN_OBJ_3(mp_oled_fill_screen_line_obj, mp_oled_fill_screen_line);

MP_STATIC const mp_rom_map_elem_t device_oled_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mp_device_oled_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear), MP_ROM_PTR(&mp_oled_clear_obj) },
    { MP_ROM_QSTR(MP_QSTR_fill_screen), MP_ROM_PTR(&mp_oled_fill_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_fill_line), MP_ROM_PTR(&mp_oled_fill_screen_line_obj) },
    { MP_ROM_QSTR(MP_QSTR_flush), MP_ROM_PTR(&mp_oled_flush_obj) },
    
	{ MP_ROM_QSTR(MP_QSTR_pixel), MP_ROM_PTR(&mp_oled_pixel_obj) },
    { MP_ROM_QSTR(MP_QSTR_hline), MP_ROM_PTR(&mp_oled_draw_hline_obj) },
    { MP_ROM_QSTR(MP_QSTR_vline), MP_ROM_PTR(&mp_oled_draw_vline_obj) },
    { MP_ROM_QSTR(MP_QSTR_line), MP_ROM_PTR(&mp_oled_draw_line_obj) },

	{ MP_ROM_QSTR(MP_QSTR_draw_arc), MP_ROM_PTR(&mp_oled_draw_arc_obj) },
    //{ MP_ROM_QSTR(MP_QSTR_draw_circle_helper), MP_ROM_PTR(&mp_oled_draw_circle_helper_obj) },
    //{ MP_ROM_QSTR(MP_QSTR_fill_circle_helper), MP_ROM_PTR(&mp_oled_fill_circle_helper_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_circle), MP_ROM_PTR(&mp_oled_draw_circle_obj) },
	{ MP_ROM_QSTR(MP_QSTR_fill_circle), MP_ROM_PTR(&mp_oled_fill_circle_obj) },
	
	{ MP_ROM_QSTR(MP_QSTR_draw_rectangle), MP_ROM_PTR(&mp_oled_draw_rectangle_obj) },
    { MP_ROM_QSTR(MP_QSTR_fill_rectangle), MP_ROM_PTR(&mp_oled_fill_rectangle_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_round_rectangle), MP_ROM_PTR(&mp_oled_draw_round_rectangle_obj) },
    { MP_ROM_QSTR(MP_QSTR_fill_round_rectangle), MP_ROM_PTR(&mp_oled_fill_round_rectangle_obj) },
    
	{ MP_ROM_QSTR(MP_QSTR_draw_ellipse), MP_ROM_PTR(&mp_oled_draw_ellipse_obj) },
	{ MP_ROM_QSTR(MP_QSTR_fill_ellipse), MP_ROM_PTR(&mp_oled_fill_ellipse_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_ellipse_rect), MP_ROM_PTR(&mp_oled_draw_ellipse_rect_obj) },
    
    { MP_ROM_QSTR(MP_QSTR_draw_triangle), MP_ROM_PTR(&mp_oled_draw_triangle_obj) },
    { MP_ROM_QSTR(MP_QSTR_fill_triangle), MP_ROM_PTR(&mp_oled_fill_triangle_obj) },

	{ MP_ROM_QSTR(MP_QSTR_line_of_arc), MP_ROM_PTR(&mp_oled_draw_line_of_arc_obj) },
    { MP_ROM_QSTR(MP_QSTR_line_of_kedu), MP_ROM_PTR(&mp_oled_draw_line_of_kedu_obj) },
    
	{ MP_ROM_QSTR(MP_QSTR_bit_map), MP_ROM_PTR(&mp_oled_draw_bit_map_obj) },
	{ MP_ROM_QSTR(MP_QSTR_show_str), MP_ROM_PTR(&mp_oled_showstr_obj) },
	{ MP_ROM_QSTR(MP_QSTR_show_str_line), MP_ROM_PTR(&mp_oled_showstr_line_obj) },
    { MP_ROM_QSTR(MP_QSTR_WHITE), MP_ROM_INT(White) },
    { MP_ROM_QSTR(MP_QSTR_BLACK), MP_ROM_INT(Black) },
};

//MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_oled_showstr_obj, 5, 6, mp_oled_showstr);


MP_DEFINE_CONST_DICT(mp_device_oled_locals_dict, device_oled_locals_dict_table);





const mp_obj_type_t device_oled_type = {
    { &mp_type_type },
    .name = MP_QSTR_OLED,
    .print = device_oled_print,
    .make_new = device_oled_make_new,
    .locals_dict = (mp_obj_dict_t *)&mp_device_oled_locals_dict,
};

#endif


