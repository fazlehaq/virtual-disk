#include<stdio.h>
#include<stdlib.h>
#include"headers/disk_utils.h"
#include"headers/types.h"
#include"headers/shareables.h"
#include"headers/file_utils.h"
#include"headers/encode_utils.h"
#include"headers/math_utils.h"

// Sharing the disk_state across multiple file 
metadata disk_state;

int main(){
	FILE *vdfp = createvd(); // Creating vdisk
	printDiskState(); // Printing the vdisk state

	while(1){
		int choice;
		printf("**********************************\nSelect your choice \n");
		printf("1.Add file\n2.ls\n3.Print disk state\n4.Get file\n5.Remove file\n6.Exit\n");
		scanf("%d",&choice);
		switch (choice){
			case 1:
				addFile(vdfp);
				break;
		
			case 2:
				ls(vdfp);
				break;

			case 3 : 
				printDiskState();
				break;
			case 4 :
				getFile(vdfp);
				break;
			case 5 :
				rm(vdfp);
				break;

			case 6 : 
				printf("Closing VD!\n");
				exit(0);

			default:
				printf("Please Enter Valid Option\n");
				break;
		}
	}

	return 0;
}


// 25bytes filname + bitsToEncode(25) + (bitsToEncodeE(8bytes MAX_ULL) * 2)