#include<stdio.h>
#include"disk_utils.h"
#include"types.h"
#include"shareables.h"

// Sharing the disk_state across multiple file 
metadata disk_state;

int main(){
	FILE *vdfp = createvd(); // Creating vdisk
	printDiskState(); // Printing the vdisk state
	addFile(vdfp); 
	addFile(vdfp);
	return 0;
}
