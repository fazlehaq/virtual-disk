#include<stdio.h>
#include"disk_utils.h"
#include"types.h"
#include"shareables.h"

metadata disk_state;

int main(){
	// printf("%lld",disk_state.diskSize);
	createvd();
	printDiskState();
	return 0;
}
