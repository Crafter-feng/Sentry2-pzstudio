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




#ifndef ENCODE_CONVERT_H
#define ENCODE_CONVERT_H



int GbkToUnicode(char *gbk_buf, unsigned short *unicode_buf, int max_unicode_buf_size);
int UnicodeToGbk(unsigned short *unicode_buf, char *gbk_buf, int max_gbk_buf_size);
int UnicodeToUtf8(unsigned long unic, unsigned char *pOutput,int outSize);
int Utf8ToUnicode(const unsigned char* pInput, unsigned long *Unic);
int unicode2gbk_test();





#endif


