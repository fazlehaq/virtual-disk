#include<stdio.h>
#include<string.h>
#include"types.h"
#include"shareables.h"
#include"constants.h"
#include"file_utils.h"
#include"disk_utils.h"
#include"encode_utils.h"
#include"math_utils.h"

#define MAX_FILE_NAME_LENGTH 25

/// @brief Add file to the vd
/// @param vdfp File pointer of the vd
void addFile(FILE *vdfp){

    // Taking filename/filepath as input
    char fileName[MAX_FILE_NAME_LENGTH];
    printf("Enter the name of the file :  ");
    scanf("%s",fileName);

    // Opening file
    FILE *fp = fopen(fileName,"rb");
    if(!fp){
        printf("Error : File doesnot exists!\n\n");
        return;
    }

    // getting the file size and checking if it gt than vdisk
    ull fileSize = getFileSize(fileName);
    if(fileSize >= disk_state.diskSize){
        printf("Cannot add file greater than disk!\n\n");
        return;
    }

    // Getting the next free block in the vd
    ull loc = getNextFreeBlock(vdfp,fileSize);
    if(loc ==-1){
        fprintf(stderr,"Unsufficient Space !\n\n");
        return;
    }

    //! This copying thing should be done after the encoding of NLP is done,
    //! coz it may happen there is enough space for one but not for other
    // Moving vd filepointer to the free block and copying the file
    // fseek(vdfp,loc,SEEK_SET);
    // copyfile(fp,vdfp);    
    // disk_state.fp = loc;
    // disk_state.fileCount++;

    // Encoding the (N,L,P) Name Length Pointer
    unsigned char buffer[MAX_BUFFER_SIZE]; // Buffer to store the encoding of the NLP pointer
    ull fileNameLen = strlen(fileName) * 8; // in bits

    // temprory buffer
    // Max possible size of the file can be respresented in 8 bytes 
    // MAX_ALLOWED length of filename is 25 hence 200 bits is max length which requires a byte  
    unsigned char buffer2[8]; 
    unsigned char fileNameLenLen;
    convShiftUnIntToByteArr(fileNameLen, &fileNameLenLen, buffer2);
    // printf(" %d ",fileNameLenLen);

    // Encoding filename length
    int pos = encode(buffer2, buffer, fileNameLenLen, 0, 0);
    if(isDebugging){   
        printf("\nPrinting encoding  %d bits ... \n",pos);
        for (size_t i = 0; i < pos; i++){
            printf("%d",getbit(buffer, i));
        }
        printf("\n");
    }

    // putting actual filename
    for(int i=pos;i<pos+(fileNameLen);i++){
        setbit(buffer,i,getbit((unsigned char *)fileName,i-pos));
    }


    // Encoding the length 
    unsigned char bitCntFileSize;
    convShiftUnIntToByteArr(fileSize,&bitCntFileSize,buffer2);
    if(isDebugging) printf("Bits required to store the fileSize is %d \n",bitCntFileSize);
    
    int pos2 = encode(buffer2,buffer,bitCntFileSize,0,pos+fileNameLen);
    if(isDebugging){
        printf("Encoding of the fileSize %llu is  : ",fileSize);
        for(int i=pos+fileNameLen;i<pos+pos2+fileNameLen; i++ )
            printf("%d",getbit(buffer,i));
        printf("\n");
    }


    // Encode the pointer
    unsigned char bitCntFilePointer;
    convShiftUnIntToByteArr(loc,&bitCntFilePointer,buffer2);
    if(isDebugging) printf("Bits required to store the filepointer are : %d \n",bitCntFilePointer);

    int pos3 = encode(buffer2,buffer,bitCntFilePointer,0,pos+fileNameLen+pos2);
    
    if(isDebugging){
        printf("Encoding of the filepointer %llu is  : ",loc);
        for(int i=pos+pos2+fileNameLen;i<pos+pos2+fileNameLen+pos3;i++)
            printf("%d",getbit(buffer,i));
    }


    // At this point encoding is done and we also have free block to store 
    // the actual file 
    // But before storing them we need to make sure the file and its pointer 
    // dont overlap 

    ull newFPP = disk_state.fpp + myCeilDiv(pos+pos2+fileNameLen+pos3 , 8);
    
    if(loc < newFPP) {
        printf("No space to add file and its metadata");
        return;
    }

    // Moving vd filepointer to the free block and copying the file
    fseek(vdfp,loc,SEEK_SET);
    copyfile(fp,vdfp);    
    // updating the disk state
    disk_state.fp = loc;
    disk_state.fileCount++;
    disk_state.fpp = newFPP;
    updateDisksMetaData(vdfp);



    // Test code to check if NLP is encoded properly
    // buffer is input
    printf("\n*******************File added*******************\n");
    char retrived_filename[MAX_FILE_NAME_LENGTH];
    ull FP = NULL;
    ull fsize = NULL;

    int fileNameLength = decode(buffer,0);
    for(int i=0;i<fileNameLength;i++){
        setbit(retrived_filename,i,getbit(buffer,i+getNumOfBitsToEncode(fileNameLength)));
    }
    for(int i=0;i<(fileNameLength/8);i++)
        printf("%c",retrived_filename[i]);
    
    fsize = decode(buffer,fileNameLength+getNumOfBitsToEncode(fileNameLength));
    printf("\nSize of the file is %d  \n",fsize);

    FP = decode(buffer,fileNameLength+getNumOfBitsToEncode(fileNameLength)+getNumOfBitsToEncode(fsize));
    printf("File starts at location %d \n",FP);

    int isLogging = 0;
    printf("Do you want to log the file ? : ");
    scanf("%d",&isLogging);

    if(isLogging) logInFile(vdfp,fsize,FP,NULL);
    
    printf("\n*******************File added*******************\n");

}

