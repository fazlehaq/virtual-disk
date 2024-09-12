#include<stdio.h>
#include<string.h>
#include"disk_utils.h"
#include"encode_utils.h"
#include"constants.h"
#include"types.h"
#include"disk_utils.h"

FILE * createvd() {
    const char * vdisk_name = "vdisk.bin";
    FILE * vdfp = fopen(vdisk_name ,"rb+");

    // check if virtual disk already exists
    if (vdfp){
        setDiskState(vdfp);
        return vdfp;
    }

    // Creating file if it doesnot eixtst
    ull vd_size;
    printf("Enter the size of vdisk in bytes \n");
    scanf("%lld",&vd_size);
    printf("%lld \n",vd_size);

    // creating new disk
    vdfp = fopen(vdisk_name,"wb");
    fclose(vdfp);
    vdfp = fopen(vdisk_name,"rb+");  

    // set data 
    const char buffer[MAX_BUFFER_SIZE];
    memset(buffer,0,MAX_BUFFER_SIZE);

    // put metadata in buffer
    // Size -> 8 || fp -> 8 || fpp -> 8 || count -> 8 ||  fpointers       ||  ---------------- || files        ||
    
    int pos1 = writeByteByByte(buffer,(ull) vd_size , sizeof(ull));
    int pos2 = writeByteByByte(buffer+pos1,(ull) vd_size,sizeof(ull));
    int pos3 = writeByteByByte(buffer+pos1+pos2, (ull) pos1+pos2+8,sizeof(ull));
    writeByteByByte(buffer+pos1+pos2+pos3, (ull) 0,sizeof(ull));
    
    if(vd_size <= MAX_BUFFER_SIZE){
        fwrite(buffer,vd_size,1,vdfp);
        setDiskState(vdfp);

        return vdfp;
    }

    fwrite(buffer,MAX_BUFFER_SIZE,1,vdfp);
    ull remaining_bytes = vd_size - MAX_BUFFER_SIZE;
    memset(buffer,0,MAX_BUFFER_SIZE);
    
    while(remaining_bytes !=0){
        if (remaining_bytes > MAX_BUFFER_SIZE){
            fwrite(buffer,1,MAX_BUFFER_SIZE,vdfp);
            remaining_bytes = remaining_bytes - MAX_BUFFER_SIZE;         
        }
        else{
            fwrite(buffer,1,remaining_bytes,vdfp);
            remaining_bytes =0;
        }
    }

    setDiskState(vdfp);
    return vdfp;
}   