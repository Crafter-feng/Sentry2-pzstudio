#include "mycrc16.h"


/* crc16校验 */
uint16 my_crc16(uint8 *buf,int len ,int invert){
    uint16 a = 0xFFFF;
    uint16 b = 0xA001;
    
    for(int i = 0; i<len; i++){
        a ^= buf[i];
        for(int j = 0; j<8; j++){
            uint8 last = a%2;
            a>>=1;
            if(last == 1){
                a ^= b;
            }
        }
    }
    uint16 tmp = 0;
    if (invert==1){
        tmp |= 0xff  & a>>8;
        tmp |= a<<8 & 0xff00;
    }else{
        tmp = a;
    }
    
    return tmp;
}







