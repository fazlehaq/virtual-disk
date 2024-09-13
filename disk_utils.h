#pragma once
#include"types.h"


FILE * createvd();
void addFile(FILE *vdfp);

void setDiskState(FILE *);
void printDiskState();
ull getNextFreeBlock(FILE *vdfp, ull fileSize);