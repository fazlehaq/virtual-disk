#include<stdio.h>
#include<string.h>
#include"types.h"
#include"shareables.h"
#include"constants.h"
#include"encode_utils.h"
#include"disk_utils.h"
#include"math_utils.h"


void ls (FILE *vdfp){
    ull fileCnt = disk_state.fileCount;
    if(fileCnt == 0){
        printf("\n********No files in the VD********\n");
        return; 
    }

    unsigned char encoding[MAX_BUFFER_SIZE];
    ull byteCnt = 0;
    fseek(vdfp,32,SEEK_SET);
    fread(encoding,MAX_BUFFER_SIZE,1,vdfp);

    while(fileCnt != 0){
        int bitCnt = 0;
        int fileNameLength = 0;
        char fileName[MAX_FILE_NAME_LENGTH] = {0};
        ull fileSize = 0;
        ull filePointer = 0;

        fileNameLength = decode(encoding,bitCnt);
        bitCnt += getNumOfBitsToEncode(fileNameLength);
        for(int i=0;i<fileNameLength*8;i++)
            setbit((unsigned char *) fileName , i , getbit(encoding,i+bitCnt));
        bitCnt += (fileNameLength *8);

        fileSize = decode(encoding,bitCnt);
        bitCnt += getNumOfBitsToEncode(fileSize);

        filePointer = decode(encoding,bitCnt);
        bitCnt += getNumOfBitsToEncode(filePointer);

        printf("%s\t%llu\t%llu\n",fileName,fileSize,filePointer);
        
        fileCnt--;

        if(fileCnt == 0) break;
        bitCnt = myCeilDiv(bitCnt,8) *8;
        byteCnt += myCeilDiv(bitCnt,8);
        fseek(vdfp, byteCnt + 32,SEEK_SET);
        fread(encoding,1,MAX_BUFFER_SIZE,vdfp);
    }
}
