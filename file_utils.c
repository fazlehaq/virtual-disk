#include<stdio.h>
#include"file_utils.h"
#include<sys/stat.h>
#include"types.h"

ull getFileSize(char *name){
    struct stat fileStat;
    if (stat(name,&fileStat) == 0){
            return (long long)fileStat.st_size;
    }
    perror("stat");
    return 0;
}