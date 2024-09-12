#include<stdio.h>
#include<string.h>
#include"disk_utils.h"
#include"constants.h"
#include"types.h"

FILE * createvd() {
    const char * vdisk_name = "vdisk.bin";
    FILE * vdfp = fopen(vdisk_name ,"rb+");

    // check if virtual disk already exists
    if (vdfp){
        return vdfp;
    }

    // Creating file if it doesnot eixtst
    ull vd_size;
    printf("Enter the size of vdisk in bytes \n");
    scanf("%lld",&vd_size);
    printf("%lld \n",vd_size);

    vdfp = fopen(vdisk_name,"wb");
    fclose(vdfp);
    vdfp = fopen(vdisk_name,"rb+");  

    printf("%d ",MAX_BUFFER_SIZE);
    // set data 
    const char buffer[MAX_BUFFER_SIZE];
    memset(buffer,0,MAX_BUFFER_SIZE);

    // put metadata in buffer
    


    return vdfp;

}   