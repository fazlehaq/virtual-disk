#include<stdio.h>
#include<string.h>
#include"headers/disk_utils.h"
#include"headers/encode_utils.h"
#include"headers/constants.h"
#include"headers/shareables.h"
#include"headers/types.h"
#include"headers/disk_utils.h"

#define METADATA_SIZE 32

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
    while(1){
        printf("Enter the size of vdisk in bytes \n");
        scanf("%lld",&vd_size);

        if(vd_size <= METADATA_SIZE) printf("Cannot create this small disk! \n");
        else break;
    }

    // creating new disk
    vdfp = fopen(vdisk_name,"wb");
    fclose(vdfp);
    vdfp = fopen(vdisk_name,"rb+");  

    // set data 
    unsigned char buffer[MAX_BUFFER_SIZE];
    memset((void *)buffer,0,MAX_BUFFER_SIZE);

    // put metadata in buffer
    // Size -> 8 || fp -> 8 || fpp -> 8 || count -> 8 ||  fpointers       ||  ---------------- || files        ||
    
    int pos1 = writeByteByByte(buffer,(ull) vd_size , sizeof(ull));
    int pos2 = writeByteByByte(buffer+pos1,(ull) vd_size,sizeof(ull));
    int pos3 = writeByteByByte(buffer+pos1+pos2, (ull) pos1+pos2+8+8,sizeof(ull));
    writeByteByByte(buffer+pos1+pos2+pos3, (ull) 0,sizeof(ull));
    
    // writing to the vdisk if vdisk < MAX_BUFFER_SIZE
    if(vd_size <= MAX_BUFFER_SIZE){
        fwrite(buffer,vd_size,1,vdfp);
        setDiskState(vdfp);
        return vdfp;
    }

    // Handling data writing to the vdisk if vdisk > MAX_BUFFER_SIZE
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

    // Setting disk state in global shared variable
    setDiskState(vdfp);
    return vdfp;
}   