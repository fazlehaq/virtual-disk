#include<stdio.h>
#include<stdlib.h>
#include"disk_utils.h"
#include"types.h"
#include"shareables.h"

// Sharing the disk_state across multiple file 
metadata disk_state;
int isDebugging  = 0;

#include"math_utils.h"
int main(){
	printf("%llu",myCeilDiv(62,8));
	printf("Are you debugging ? : ");
	scanf("%d",&isDebugging);
	FILE *vdfp = createvd(); // Creating vdisk
	printDiskState(); // Printing the vdisk state

	// addFile(vdfp);
	// addFile(vdfp);
	ls(vdfp);

	// while(1){
	// 	int choice;
	// 	printf("*****************\nSelect your choice \n");
	// 	printf("1.Add file\n2.ls\n3.Exit");
	// 	scanf("%d",&choice);
	// 	switch (choice){
	// 		case 1:
	// 			addFile(vdfp);
	// 			break;
		
	// 		case 2:
	// 			ls(vdfp);
	// 			break;

	// 		case 3 : 
	// 			printf("Closing VD!\n");
	// 			exit(0);

	// 		default:
	// 			printf("Please Enter Valid Option\n");
	// 			break;
	// 	}
	// }

	// return 0;
}
