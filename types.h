#pragma once
#include"constants.h"

typedef unsigned long long ull; 

typedef struct metadata{
    ull diskSize;
    ull fp;
    ull fpp;
    ull fileCount;
}  metadata;

typedef struct vdfile{
    char name[MAX_FILE_NAME_LENGTH];
    ull size;
    ull location;
}vdfile;