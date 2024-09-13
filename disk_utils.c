#include<stdio.h>
#include"disk_utils.h"
#include"encode_utils.h"
#include"shareables.h"
#include"types.h"

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
    printf("\nDisk States :\ndiskSize : %lld \nFp : %lld \nFPP : %lld\nFileCount : %lld\n",disk_state.diskSize,disk_state.fp,disk_state.fpp,disk_state.fileCount);
}

/// @brief Returns the next free block for the addFile functionality
/// @param vdfp File pointer to the vd
/// @param fileSize File size to store 
/// @return [ Loc in vd if available | -1 if not available ]
ull getNextFreeBlock(FILE *vdfp, ull fileSize){
    //Naive Approach
    ull addloc = disk_state.fp - fileSize;
    if(addloc <= disk_state.fpp){
        return -1;
    }
    return addloc;
}