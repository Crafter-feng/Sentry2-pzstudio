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







