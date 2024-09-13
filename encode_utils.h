#pragma once
#include"types.h"

int writeByteByByte(unsigned char* in,ull number ,int byteCount);
ull byteToULL(unsigned char* byteArr, int byteCount);
int getbit(unsigned char *in,unsigned int n);
void setbit(unsigned char *out,unsigned int n, int k);
int encode(unsigned char* in, unsigned char* out,unsigned char n , unsigned char level, short int bitoffset);
ull decode(unsigned char* in,short int bitoffset);
unsigned char* convShiftUnIntToByteArr(ull Integer, unsigned char *length,unsigned char *out);