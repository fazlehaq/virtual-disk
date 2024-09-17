#pragma once
#include"types.h"

int writeByteByByte(unsigned char* in,ull number ,int byteCount);
ull byteToULL(unsigned char* byteArr, int byteCount);
int getbit(unsigned char *in,ull n);
void setbit(unsigned char *out,ull n, int k);
int encode(unsigned char* in, unsigned char* out,unsigned char n , unsigned char level, unsigned int bitoffset);
ull decode(unsigned char* in,ull bitoffset);
unsigned char* convShiftUnIntToByteArr(ull Integer, unsigned char *length,unsigned char *out);
ull getNumOfBitsToEncode(ull n);