#include<stdio.h>
#include"types.h"
#include<sys/stat.h>
#define MAX_FILE_NAME_LENGTH 25


ull getFileSize(char *name){
    struct stat fileStat;
    if (stat(name,&fileStat) == 0){
            return (long long)fileStat.st_size;
    }
    perror("stat");
    return 0;
}

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


