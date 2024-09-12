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


