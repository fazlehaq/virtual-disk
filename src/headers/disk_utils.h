#pragma once
#include"types.h"



FILE* createvd();
void addFile(FILE* vdfp);
void ls(FILE* vdfp);
void getFile(FILE* fp);
void rm(FILE* vdfp);

void setDiskState(FILE *);
void printDiskState();
ull getNextFreeBlock(FILE *vdfp, ull fileSize);
void logInFile(FILE *vdfp,ull length,ull offset, char *filename);
void updateDisksMetaData(FILE *vdfp);
