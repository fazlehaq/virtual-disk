#include<stdio.h>
#include"disk_utils.h"
#include"types.h"
#include"shareables.h"

metadata disk_state;

int main(){
	createvd();
	printDiskState();
	return 0;
}
