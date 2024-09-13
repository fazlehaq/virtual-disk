#include<stdio.h>
#include<string.h>
#include"types.h"
#include"shareables.h"
#include"constants.h"
#include"file_utils.h"
#include"disk_utils.h"
#include"encode_utils.h"

#define MAX_FILE_NAME_LENGTH 25

/// @brief Add file to the vd
/// @param vdfp File pointer of the vd
void addFile(FILE *vdfp){
    // Taking filename/filepath as input
    char fileName[MAX_FILE_NAME_LENGTH];
    printf("Enter the name of the file :  ");
    scanf("%s",fileName);
    printf("\n");

    // Opening file
    FILE *fp = fopen(fileName,"rb");
    if(!fp){
        printf("Error : File doesnot exists!\n");
        return;
    }

    // Getting the next free block in the vd
    ull fileSize = getFileSize(fileName);
    ull loc = getNextFreeBlock(vdfp,fileSize);
    if(loc ==-1){
        fprintf(stderr,"No space to add file");
        return;
    }

    //! This copying thing should be done after the encoding of NLP is done,
    //! coz it may happen there is enough space for one but not for other
    // Moving vd filepointer to the free block and copying the file
    fseek(vdfp,loc,SEEK_SET);
    copyfile(fp,vdfp);    
    disk_state.fp = loc;
    disk_state.fileCount++;

    // Encoding the (N,L,P) Name Length Pointer
    unsigned char buffer[MAX_BUFFER_SIZE];
    ull fileNameLen = strlen(fileName) * 8; // in bits
    unsigned char buffer2[20];
    unsigned char fileNameLenLen;
    convShiftUnIntToByteArr(fileNameLen, &fileNameLenLen, buffer2);
    printf("%d ",fileNameLenLen);

    int pos = encode(buffer2, buffer, fileNameLenLen, 0, 0);
    printf("\n Printing encoding... \n");
    for (size_t i = 0; i < pos; i++){
        printf("%d",getbit(buffer, i));
    }
    
}


