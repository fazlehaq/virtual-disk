#include<stdio.h>
#include"disk_utils.h"
#include"shareables.h"
#include"types.h"

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

