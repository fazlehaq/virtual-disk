#include<stdio.h>
#include<string.h>
#include"math_utils.h"
#include"constants.h"
#include"shareables.h"
#include"encode_utils.h"
#include"disk_utils.h"
#include"file_utils.h"
#include"types.h"


void getFile(FILE *vdfp){
    if(disk_state.fileCount == 0) { printf("No files in the vd\n"); return; }
    char fileName[MAX_FILE_NAME_LENGTH] = {0};
    scanf("%s",fileName);

    if(strlen(fileName) == 0) { printf("Please enter valid filename\n"); return; }

    ull fileCount = disk_state.fileCount;
    unsigned char buffer[MAX_BUFFER_SIZE];
    fseek(vdfp,32,SEEK_SET);
    fread(buffer,MAX_BUFFER_SIZE,1,vdfp);
    int byteCnt = 0;

    // infinite loop
    while (1){
        int bitCnt = 0;
        char currFileName[MAX_FILE_NAME_LENGTH] = {0};
        ull fileSize = 0;
        ull filePointer = 0;

        int currFileNameLength = decode(buffer,bitCnt);
        bitCnt += getNumOfBitsToEncode(currFileNameLength);
        for(int i=0;i<8*currFileNameLength;i++)
            setbit((unsigned char *)currFileName,i,getbit(buffer,i+bitCnt));
        bitCnt += (8*currFileNameLength);

        fileSize = decode(buffer,bitCnt);
        bitCnt += getNumOfBitsToEncode(fileSize);

        filePointer = decode(buffer,bitCnt);
        bitCnt += getNumOfBitsToEncode(filePointer);

        if(strcmp(fileName,currFileName) == 0) { 
            // vdfile *matchedFile = (vdfile *) malloc(sizeof(vdfile));
            printf("File found\n"); 
            fseek(vdfp,filePointer,SEEK_SET);
            FILE * output= fopen("output","wb");
            copyfile(vdfp,output,fileSize);
            fclose(output);
            return; 
        }
        fileCount--;
        if(fileCount == 0) {printf("File not found \n"); break;}

        byteCnt += myCeilDiv(bitCnt,8);
        fseek(vdfp,32+byteCnt,SEEK_SET);
        fread(buffer,MAX_BUFFER_SIZE,1,vdfp);
    }
    
}