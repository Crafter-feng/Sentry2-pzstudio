#ifndef ENCODE_CONVERT_H
#define ENCODE_CONVERT_H



int GbkToUnicode(char *gbk_buf, unsigned short *unicode_buf, int max_unicode_buf_size);
int UnicodeToGbk(unsigned short *unicode_buf, char *gbk_buf, int max_gbk_buf_size);
int UnicodeToUtf8(unsigned long unic, unsigned char *pOutput,int outSize);
int Utf8ToUnicode(const unsigned char* pInput, unsigned long *Unic);
int unicode2gbk_test();





#endif


