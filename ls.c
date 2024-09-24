#include<stdio.h>
#include<string.h>
#include"types.h"
#include"shareables.h"
#include"constants.h"
#include"encode_utils.h"
#include"disk_utils.h"
#include"math_utils.h"

// Calculating the max number of bytes to store the encoding of the pointer
#define MAX_BYTES_PER_FILE_POINTER_ENCODING myCeilDiv ((25*8)+getNumOfBitsToEncode(25)+(2*(getNumOfBitsToEncode(0xFFFFFFFFFFFFFFFF))),8)


void ls (FILE *vdfp){
    ull fileCnt = disk_state.fileCount;
    if(fileCnt == 0){
        printf("\n********No files in the VD********\n");
        return; 
    }
    
    int maxPointersInBuffer = (MAX_BUFFER_SIZE/MAX_BYTES_PER_FILE_POINTER_ENCODING);// calculating how many complete pointers we can have in the buffer 
    int currPointerCnt = 0; // keeping track for the pointer read from buffer
    unsigned char encoding[MAX_BUFFER_SIZE];
    ull byteCnt = 0;
    fseek(vdfp,32,SEEK_SET);
    fread(encoding,MAX_BUFFER_SIZE,1,vdfp);
    int encodingBitCnt = 0;

    while(fileCnt != 0){
        int fileNameLength = 0;
        char fileName[MAX_FILE_NAME_LENGTH] = {0};
        ull fileSize = 0;
        ull filePointer = 0;
        int bitReadCnt = 0; // bitsRead in current pointer

        fileNameLength = decode(encoding,encodingBitCnt);
        bitReadCnt += getNumOfBitsToEncode(fileNameLength);
        for(int i=0;i<fileNameLength*8;i++)
            setbit((unsigned char *) fileName , i , getbit(encoding,i+encodingBitCnt+bitReadCnt));
        bitReadCnt += (fileNameLength *8);

        fileSize = decode(encoding,encodingBitCnt+bitReadCnt);
        bitReadCnt += getNumOfBitsToEncode(fileSize);

        filePointer = decode(encoding,encodingBitCnt+bitReadCnt);
        bitReadCnt += getNumOfBitsToEncode(filePointer);

        printf("%s\t%llu\t%llu\n",fileName,fileSize,filePointer);
        
        fileCnt--;
        currPointerCnt++;

        if(fileCnt == 0) break;
        encodingBitCnt += myCeilDiv(bitReadCnt,8) *8;
        byteCnt += myCeilDiv(bitReadCnt,8);
        if(currPointerCnt == 5){
            fseek(vdfp, byteCnt + 32,SEEK_SET);
            printf("%ld\n" ,ftell(vdfp));
            fread(encoding,1,MAX_BUFFER_SIZE,vdfp);
            currPointerCnt = 0;
            encodingBitCnt = 0;
        }
    }
}
