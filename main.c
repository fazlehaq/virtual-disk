#include<stdio.h>
#include"disk_utils.h"
#include"types.h"
#include"shareables.h"

// Sharing the disk_state across multiple file 
metadata disk_state;
int isDebugging  = 0;


int main(){
	printf("Are you debugging ? : ");
	scanf("%d",&isDebugging);
	FILE *vdfp = createvd(); // Creating vdisk
	printDiskState(); // Printing the vdisk state
	while(1){
		addFile(vdfp); 
		printDiskState();
	}

	return 0;
}
