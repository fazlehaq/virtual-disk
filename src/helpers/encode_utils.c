#include<stdio.h>
#include<math.h>
#include"../headers/types.h"
#include"../headers/encode_utils.h"
#include"../headers/math_utils.h"

/// @brief Given a number we put its bytes in an unsigned char array
/// @return number of bytes stored
// This works by shifting the bytes (we want to insert in the array)
// to the LSB in the number then cast it to the unsigned char which keeps only the required byte
// then we store the byte in given array 
int writeByteByByte(unsigned char *in,ull number,int byteCount){

    for(int i=0;i<byteCount;i++){
        in[i] = (unsigned char) ( number >> ((8*(byteCount-i))-8) ); 
    }

    return byteCount;    
}


/// @brief Given a byte array we transform it to the unsigned long long
/// @return the number equvivalent to byte array 
/// This works by traversing over the given byte array 
/// Then for each byte we first cast it to unsigned long long
/// Then put the extracted byte in the correct position by shifting left
/// Then we bitwise or that number with our result which is initialized as 0
unsigned long long byteToULL(unsigned char* byteArr, int byteCount){
    ull res = 0;
    for(int i=0;i<byteCount;i++){
        ull temp = byteArr[i];
        temp = temp << (8*(byteCount - 1 - i));
        res = res | temp;
    }
    return res;
}

/// @brief Return the specified bit in the given byte array
/// @param in Byte array
/// @param n Specific bit number
/// @return 0 or 1 
int getbit(unsigned char *in,ull n){
	unsigned char mask[] ={128,64,32,16,8,4,2,1};
	return (in[(n/8)] & mask[n%8]) == 0 ? 0 : 1;
}

/// @brief Given byte array it sets the specific bit to specific value 
/// @param out Byte array
/// @param n Bit number
/// @param k Bit value [0 | 1]
void setbit(unsigned char *out,ull n, int k){
	unsigned char mask[] ={128,64,32,16,8,4,2,1};
	if(k == 0) 
		out[(n/8)] = (out[(n/8)] & (~mask[(n%8)]));
	else 
		out[(n/8)] = (out[(n/8)] | mask[(n%8)]);
}

unsigned char* convertUnIntToByteArr(unsigned int number,unsigned char *arr){
	for(int i=0;i<4;i++){
		arr[i] =((unsigned char) (number >> ((3-i)*8))) & 0xFF;
//		printf("%b",arr[i]);
	}

	return arr;
}

unsigned int convertByteArrToUnInt(unsigned char *arr){	
	unsigned int number = 0;
	for(int i=0;i<4;i++){	
		number = number | (((unsigned int) arr[i]) << ((3-i)*8));
	}
	
	printf("%d ",number);
	return number;
}

unsigned char* convShiftUnIntToByteArr(ull Integer, unsigned char *length,unsigned char *out){
        int count = sizeof(unsigned long long) * 8;
    
        // calculating count of actual bits and shifting msb to 1
        while((myPow(2, (sizeof(unsigned long long) * 8)-1) & Integer ) == 0){ 
                Integer = Integer << 1;
                count -=1;
        }
		*length = count;
    
	// returning the pointer to the byte array
        int byteRequired = (unsigned int) ceil( (double) count/(double) 8); 
    
        for(int i=0;i<byteRequired; i++){
                out[i] = (unsigned char) (Integer >> (((sizeof(unsigned long long)-1)-i) * 8)) & 0xFF;
        }
    
        return out;
}
