#include<stdio.h>
#include<string.h>
#include"headers/math_utils.h"
#include"headers/constants.h"
#include"headers/shareables.h"
#include"headers/encode_utils.h"
#include"headers/disk_utils.h"
#include"headers/file_utils.h"
#include"headers/types.h"


void getFile(FILE *vdfp){
    if(disk_state.fileCount == 0) { printf("No files in the vd\n"); return; }
    char fileName[MAX_FILE_NAME_LENGTH] = {0};
    printf("Enter the name of the file : ");
    scanf("%s",fileName);

    if(strlen(fileName) == 0) { printf("Please enter valid filename\n"); return; }

    ull fileCount = disk_state.fileCount;
    int maxPointersInBuffer = (MAX_BUFFER_SIZE/MAX_BYTES_PER_FILE_POINTER_ENCODING);// calculating how many complete pointers we can have in the buffer
    int currPointerCnt = 0;
    unsigned char encoding[MAX_BUFFER_SIZE];
    ull byteCnt = 0;
    int encodingBitCnt = 0;
    fseek(vdfp,32,SEEK_SET);
    fread(encoding,MAX_BUFFER_SIZE,1,vdfp);

    // infinite loop
    while (1){
        int currFileNameLength = 0;
        char currFileName[MAX_FILE_NAME_LENGTH] = {0};
        ull fileSize = 0;
        ull filePointer = 0;
        int bitReadCnt = 0;
        int isRemoved = 0;

        isRemoved = getbit(encoding,encodingBitCnt+bitReadCnt);
        bitReadCnt++;

        currFileNameLength = decode(encoding,encodingBitCnt+bitReadCnt);
        bitReadCnt += getNumOfBitsToEncode(currFileNameLength);

        for(int i=0;i<8*currFileNameLength;i++)
            setbit((unsigned char *)currFileName,i,getbit(encoding,i+ encodingBitCnt+bitReadCnt));
        bitReadCnt += (8*currFileNameLength);

        fileSize = decode(encoding,encodingBitCnt+bitReadCnt);
        bitReadCnt += getNumOfBitsToEncode(fileSize);

        filePointer = decode(encoding,encodingBitCnt+bitReadCnt);
        bitReadCnt += getNumOfBitsToEncode(filePointer);

        if(isRemoved == 0 && strcmp(fileName,currFileName) == 0) { 
            // vdfile *matchedFile = (vdfile *) malloc(sizeof(vdfile));
            printf("File found\n"); 
            fseek(vdfp,filePointer,SEEK_SET);
            FILE * output= fopen("output","wb");
            copyfile(vdfp,output,fileSize);
            fclose(output);
            printf("File copied in output\n"); 
            return; 
        }
        
        if(isRemoved == 0)
            fileCount--;

        if(fileCount == 0) {printf("File not found \n"); break;}

        encodingBitCnt += myCeilDiv(bitReadCnt,8) * 8;
        byteCnt += myCeilDiv(bitReadCnt,8);

        if(currPointerCnt == maxPointersInBuffer){

            fseek(vdfp,32+byteCnt,SEEK_SET);
            fread(encoding,MAX_BUFFER_SIZE,1,vdfp);
            currPointerCnt = 0;
            encodingBitCnt = 0;
        }
    }
    
}