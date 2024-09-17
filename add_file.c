#include<stdio.h>
#include<string.h>
#include"types.h"
#include"shareables.h"
#include"constants.h"
#include"file_utils.h"
#include"disk_utils.h"
#include"encode_utils.h"
#include"math_utils.h"


/// @brief Add file to the vd
/// @param vdfp File pointer of the vd
void addFile(FILE *vdfp){

    // Taking filename/filepath as input
    char fileName[MAX_FILE_NAME_LENGTH];
    printf("Enter the name of the file :  ");
    scanf("%s",fileName);
    printf("%s\n",fileName);

    if(strlen(fileName) > MAX_FILE_NAME_LENGTH) {
        printf("Max character allowed for filename is %d \n",MAX_FILE_NAME_LENGTH);
        return;
    }

    // Opening file
    FILE *fp = fopen(fileName,"rb");
    if(!fp){
        printf("Error : File doesnot exists!\n\n");
        return;
    }

    // getting the file size and checking if it gt than vdisk
    ull fileSize = getFileSize(fileName);
    if(fileSize >= disk_state.diskSize){
        printf("Cannot add file greater than disk!\n\n");
        return;
    }

    // Getting the next free block in the vd
    ull loc = getNextFreeBlock(vdfp,fileSize);
    if(loc ==-1){
        fprintf(stderr,"Unsufficient Space !\n\n");
        return;
    }

    // Now well encode the N,L,P pointer and check if we have space for this in vd 
    // if yes we store the pointer and actual file both.

    unsigned char encoding[MAX_BUFFER_SIZE] = {0};
    ull fileNameLength = strlen(fileName);
    int bitOffset = 0;
    int boff = 0;
    
    unsigned char temp_buffer[8] = {0}; // to store byteArr representation 
    unsigned char bitsCnt;
    convShiftUnIntToByteArr(fileNameLength,&bitsCnt,temp_buffer);
    int pos1 = encode(temp_buffer,encoding,bitsCnt,0,bitOffset);
    bitOffset += pos1;
    boff += getNumOfBitsToEncode(fileNameLength);
    // printf("\n pos -> %llu  encoded -> %llu",pos1,getNumOfBitsToEncode(fileNameLength));

    for(int i=0;i<8*fileNameLength;i++)
        setbit(encoding,(ull)(i+bitOffset),getbit((unsigned char *)fileName,(ull)i));
    
    bitOffset += (fileNameLength*8);
    boff += (fileNameLength*8);
    // printf("\n pos -> %llu  encoded -> %llu",fileNameLength*8,fileNameLength*8);



    // encoding the fileSize
    bitsCnt = 0;
    convShiftUnIntToByteArr(fileSize,&bitsCnt,temp_buffer);
    int pos2 = encode(temp_buffer,encoding,bitsCnt,0,bitOffset);
    bitOffset += pos2;

    //encoding the filePointer
    bitsCnt = 0;
    convShiftUnIntToByteArr(loc,&bitsCnt,temp_buffer);
    int pos3= encode(temp_buffer,encoding,bitsCnt,0,bitOffset);
    bitOffset += pos3;

    // Now the encoding is done we'll check if there is space for it in vd
    ull newFpp = disk_state.fpp + myCeilDiv(bitOffset,8);
    if(loc < newFpp){
        printf("Not enough storage for metadata\n");
        return;
    }

    // move the file pointer to store the fpp
    fseek(vdfp,disk_state.fpp,SEEK_SET);
    fwrite(encoding,1,myCeilDiv(bitOffset,8),vdfp);
    disk_state.fpp = newFpp;

    // move the file pointer to store the actual data
    fseek(vdfp,loc,SEEK_SET);
    copyfile(fp,vdfp,NULL);
    fclose(fp);
    disk_state.fp = loc;
    disk_state.fileCount++;

    updateDisksMetaData(vdfp);
    
    printf("********File Added********\n");
    //  cheking the encoding
    int filenamelen = decode(encoding,0);
    char filename[25] = {0};
    int bits = getNumOfBitsToEncode(filenamelen);
    for(int i=0;i<filenamelen*8;i++)
        setbit((unsigned char *)filename,i,getbit(encoding,i+bits));
    for(int i=0;i<filenamelen;i++)
        printf("%c",filename[i]);
    bits += 8*filenamelen;
    ull fsize = decode(encoding,bits);
        printf("\t%llu",fsize);
        bits+=getNumOfBitsToEncode(fsize);
    ull fpp = decode(encoding,bits);
        printf("\t%llu",fpp);
    // printf("\nBytes for encoding : %llu %llu",myCeilDiv(bitOffset,8),myCeilDiv(boff,8));

    printf("\n********File Added********\n");

    // for(int i=0;i<myCeilDiv(bitOffset,8);i++){
    //     for(int j=0;j<8;j++){
    //         printf("%d",getbit(encoding,((i*8)+j)));
    //     }
    //     printf(" ");
    // }
}

