#include<stdio.h>
#include"../headers/disk_utils.h"
#include"../headers/encode_utils.h"
#include"../headers/shareables.h"
#include"../headers/constants.h"
#include"../headers/types.h"

/// @brief Set the disk_state global values by extracting them from vd
/// @param vdfp File Pointer of the vd
void setDiskState(FILE *vdfp){
    fseek(vdfp,0,SEEK_SET);
    unsigned char buffer[8] = {0};
    fread(buffer,8,1,vdfp);
    disk_state.diskSize = byteToULL(buffer ,8);
    fread(buffer,8,1,vdfp);
    disk_state.fp=byteToULL(buffer,8);
    fread(buffer,8,1,vdfp);
    disk_state.fpp=byteToULL(buffer ,8);
    fread(buffer,8,1,vdfp);
    disk_state.fileCount=byteToULL(buffer,8);
}

void printDiskState(){
    printf("\n**********************************\nDisk States :\ndiskSize : %lld \nFp : %lld \nFPP : %lld\nFileCount : %lld\n**********************************\n",disk_state.diskSize,disk_state.fp,disk_state.fpp,disk_state.fileCount);
}

/// @brief Returns the next free block for the addFile functionality
/// @param vdfp File pointer to the vd
/// @param fileSize File size to store 
/// @return [ Loc in vd if available | -1 if not available ]
ull getNextFreeBlock(FILE *vdfp, ull fileSize){
    //Naive Approach
    ull addloc = disk_state.fp - fileSize;
    // first condition is simply overlap
    // second condition is overflow > example we have too big file well get add loc as negative but ull will make it extra large number 
    if(addloc <= disk_state.fpp || addloc > disk_state.fp){
        return -1;
    }
    return addloc;
}


void logInFile(FILE *vdfp,ull length,ull offset,char *filename){
    fseek(vdfp,offset,SEEK_SET);
    FILE *logfp = fopen(filename,"wb");

    ull remaining_bytes = length;
    char buffer[MAX_BUFFER_SIZE] = {0};

    while(remaining_bytes > MAX_BUFFER_SIZE){
        fread(buffer,MAX_BUFFER_SIZE,1,vdfp);
        fwrite(buffer,MAX_BUFFER_SIZE,1,logfp);
        remaining_bytes -= MAX_BUFFER_SIZE;
    }

    fread(buffer,remaining_bytes,1,vdfp);
    fwrite(buffer,remaining_bytes,1,logfp);
    fclose(logfp);
}

void updateDisksMetaData(FILE *vdfp){
    fseek(vdfp,8,SEEK_SET);

    unsigned char buffer[8];
    writeByteByByte(buffer,disk_state.fp,8);
    fwrite(buffer,8,1,vdfp);
    writeByteByByte(buffer,disk_state.fpp,8);
    fwrite(buffer,8,1,vdfp);
    writeByteByByte(buffer,disk_state.fileCount,8);
    fwrite(buffer,8,1,vdfp);
}