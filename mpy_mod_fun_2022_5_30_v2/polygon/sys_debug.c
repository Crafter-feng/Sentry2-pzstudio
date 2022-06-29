#include <stdio.h>
#include <stdarg.h>
#include "sys_debug.h"


#if SYS_DEBUG_ENABLE==1


 #if 0
//==================================================================================================
typedef char *  va_list;

/* va_start,va_arg, va_end,宏的用法在可变参数函数中有具体介绍*/
 
#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
 
#define va_start(ap,v)  ( ap = (va_list)&v + _INTSIZEOF(v) )
//#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_arg(ap,t)    ( *(t *)( ap=ap + _INTSIZEOF(t), ap- _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (va_list)0 )
//==================================================================================================
#endif
unsigned char hex_tab[]={'0','1','2','3','4','5','6','7',\
		                 '8','9','a','b','c','d','e','f'};




/* __out_putchar是宏定义putchar
实际会调用uart.c中的putchar函数来输出字符 */
static int outc(int c) 
{
	console_print(c);
	return 0;
}







/* 输出字符串 */
static int outs (const char *s)
{
	while (*s != '\0')	
		console_print(*s++);
	return 0;
}





/* 根据数字n, 进制base,前导码lead,最大长度maxwidth,构造需要得到的字符串 */
static int out_num(long n, int base,char lead,int maxwidth) 
{
	unsigned long m=0;
	/* 数字字符串的长度最大为MAX_NUMBER_BYTES=64个 */
	/* s指向buf数组的最后 */
	char buf[MAX_NUMBER_BYTES], *s = buf + sizeof(buf);
	int count=0,i=0;
	*--s = '\0';
 
	/* 传入负值时取绝对值,最后在前面输出'-' */
	if (n < 0){
		m = -n;
	}
	else{
		m = n;
	}
 
	/* 根据进制得到每一位,存放在s中 */
	/* 权重低的会先存放在s中,存放完成之后s-- */
	do{
		*--s = hex_tab[m%base];
		count++;			/* 计算数字的个数 */
	}while ((m /= base) != 0);
 
	/* 根据数字的最大长度设置前导码 */
	if( maxwidth && count < maxwidth){
		for (i=maxwidth - count; i; i--)	
			*--s = lead;	
}
 
	if (n < 0)
		*--s = '-';
 
	/* 输出数字字符串 */
	return outs(s);
}





/*reference :   int vprintf(const char *format, va_list ap); */
static int my_vprintf(const char *fmt, va_list ap) 
{
	char lead=' ';		/* 前导码默认是空格 */
	int  maxwidth=0;	/* 字符串的最大长度 */
 
 
	 /* 在fmt字符串中寻找到%符号 */
	 for(; *fmt != '\0'; fmt++)
	 {
			if (*fmt != '%') {
				outc(*fmt);
				continue;
			}
		lead=' ';
		maxwidth=0;
		
		//format : %08d, %8d,%d,%u,%x,%f,%c,%s 
		    fmt++;		/* fmt指向%的下一个字符 */
		/* 判断前导码是不是'0' */
		if(*fmt == '0'){
			lead = '0';
			fmt++;	
		}
 
		/* 设置最大输出长度 */
		while(*fmt >= '0' && *fmt <= '9'){
			maxwidth *=10;
			maxwidth += (*fmt - '0');
			fmt++;
		}
 
		/* 根据输出格式输出对应字符串 */
			switch (*fmt) {
		case 'd': out_num(va_arg(ap, int),          10,lead,maxwidth); break;
		case 'o': out_num(va_arg(ap, unsigned int),  8,lead,maxwidth); break;				
		case 'u': out_num(va_arg(ap, unsigned int), 10,lead,maxwidth); break;
		case 'x': out_num(va_arg(ap, unsigned int), 16,lead,maxwidth); break;
			case 'c': outc(va_arg(ap, int   )); break;		
			case 's': outs(va_arg(ap, char *)); break;		  		
				
			default:  
				outc(*fmt);
				break;
			}
	}
	return 0;
}




//reference :  int printf(const char *format, ...); 
int sys_printf(const char *fmt, ...) 
{
	va_list ap;
	va_start(ap, fmt);
	my_vprintf(fmt, ap);	
	va_end(ap);
	return 0;
}






void Sys_Debug_Init(void){
	Sys_Debug_Uart_Init(115200);
}


#else
void Sys_Debug_Init(void){
	
}


#endif



