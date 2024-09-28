#pragma once
#include"types.h"
#include"math_utils.h"

int writeByteByByte(unsigned char* in,ull number ,int byteCount);
ull byteToULL(unsigned char* byteArr, int byteCount);
int getbit(unsigned char *in,ull n);
void setbit(unsigned char *out,ull n, int k);
int encode(unsigned char* in, unsigned char* out,unsigned char n , unsigned char level, unsigned int bitoffset);
ull decode(unsigned char* in,ull bitoffset);
unsigned char* convShiftUnIntToByteArr(ull Integer, unsigned char *length,unsigned char *out);
ull getNumOfBitsToEncode(ull n);
// Calculating the max number of bytes to store the encoding of the pointer
#define MAX_BYTES_PER_FILE_POINTER_ENCODING myCeilDiv ((25*8)+getNumOfBitsToEncode(25)+(2*(getNumOfBitsToEncode(0xFFFFFFFFFFFFFFFF))),8)