#include<stdio.h>
#include"types.h"
#include"shareables.h"
#define MAX_FILE_NAME_LENGTH 25




ull getNextFreeBlock(FILE *vdfp){

}

void addFile(FILE *vdfp){
    
    char fileName[25];
    printf("Enter the name of the file :  ");
    scanf("%s",fileName);
    printf("\n");

    FILE *fp = fopen(fileName,"rb");
    if(!fp){
        printf("Error : File doesnot exists!\n");
        return;
    }

    ull fileSize = getFileSize(fileName);

    getNextFreeBlock(vdfp);

}


