#include<stdio.h>
#include<string.h>
#include"types.h"
#include"shareables.h"
#include"constants.h"
#include"encode_utils.h"
#include"disk_utils.h"
#include"math_utils.h"

void ls(FILE *vdfp) {
    ull fileCount = disk_state.fileCount;
    if(fileCount == 0) return;

    // moving the file pointer to the pointers start
    fseek(vdfp,32,SEEK_SET);
    
    // declaring variables
    unsigned char buffer[MAX_BUFFER_SIZE];
    char fileName[MAX_FILE_NAME_LENGTH];
    ull fileSize;
    ull currReadingBitNumber = 0;
    ull totalBits = 0;
    fread ((void *)buffer,MAX_BUFFER_SIZE,1,vdfp);

    printf("filename\tsize(in bytes)\n");

    while(fileCount != 0){
        printf("reading pointer\n");

        int fileNamelength = decode(buffer,currReadingBitNumber);
        currReadingBitNumber += getNumOfBitsToEncode(fileNamelength);

        printf("setting filename\n");
        for(int i=0;i<fileNamelength;i++){
            setbit((unsigned char *)fileName,i,getbit( buffer,i+currReadingBitNumber));
        }
        currReadingBitNumber += fileNamelength;
        printf("%s  %llu\n",fileName,fileSize);

        printf("setting filesize\n");
        fileSize = decode(buffer,currReadingBitNumber);
        currReadingBitNumber += getNumOfBitsToEncode(fileSize);

        printf("getting filepointer\n");
        ull filePointer = decode(buffer,currReadingBitNumber);
        printf("got the filepointer\n");
        currReadingBitNumber += getNumOfBitsToEncode(filePointer);

        printf("%s  %llu\n",fileName,fileSize);

        fileCount--;

        //
        if(fileCount == 0) break;

        // if (currReadingBitNumber % 8 != 0){
        //     fseek(vdfp,-1,SEEK_CUR);
        //     currReadingBitNumber %= 8;
        // }
        // else{
        // }
        memset(fileName,0,MAX_FILE_NAME_LENGTH);
        fseek(vdfp,32+myCeilDiv(currReadingBitNumber,8),SEEK_SET);
        fread(buffer,1,MAX_BUFFER_SIZE,vdfp);
        // totalBits += currReadingBitNumber;
        currReadingBitNumber = 0;
    }
}  