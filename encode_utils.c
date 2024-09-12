#include<stdio.h>
#include"types.h"
#include"encode_utils.h"

int writeByteByByte(unsigned char *in,ull number,int byteCount){
    unsigned char byte = 0xFF;

    for(int i=0;i<byteCount;i++){
        in[i] = (unsigned char) ( number >> ((8*(byteCount-i))-8) );
        printf("%llu ",in[i]);
    }

    return byteCount;    
}


unsigned long long byteToULL(unsigned char* byteArr, int byteCount){
    ull res = 0;
    for(int i=0;i<byteCount;i++){
        ull temp = byteArr[i];
        temp = temp << (8*(byteCount - 1 - i));
        res = res | temp;
    }
    return res;
} 
