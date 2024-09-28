#include <stdio.h>
#include <string.h>
#include "headers/types.h"
#include "headers/shareables.h"
#include "headers/constants.h"
#include "headers/encode_utils.h"
#include "headers/disk_utils.h"
#include "headers/math_utils.h"


void rm(FILE *vdfp)
{
    ull fileCnt = disk_state.fileCount;
    if (fileCnt == 0)
    {
        printf("\n********No files in the VD********\n");
        return;
    }
    char fileNameToRemove[MAX_FILE_NAME_LENGTH] = {0};
    printf("Enter the name of the file to remove : ");
    scanf("%s", fileNameToRemove);
    printf("%s\n", fileNameToRemove);

    int maxPointersInBuffer = (MAX_BUFFER_SIZE / MAX_BYTES_PER_FILE_POINTER_ENCODING); // calculating how many complete pointers we can have in the buffer
    int currPointerCnt = 0;                                                            // keeping track for the pointer read from buffer
    unsigned char encoding[MAX_BUFFER_SIZE];
    ull byteCnt = 0;
    fseek(vdfp, 32, SEEK_SET);
    fread(encoding, MAX_BUFFER_SIZE, 1, vdfp);
    int encodingBitCnt = 0;

    while (fileCnt != 0)
    {
        int fileNameLength = 0;
        char fileName[MAX_FILE_NAME_LENGTH] = {0};
        ull fileSize = 0;
        ull filePointer = 0;
        int bitReadCnt = 0; // bitsRead in current pointer

        int isRemoved = getbit(encoding, encodingBitCnt + bitReadCnt);
        bitReadCnt++;

        fileNameLength = decode(encoding, encodingBitCnt + bitReadCnt);
        bitReadCnt += getNumOfBitsToEncode(fileNameLength);
        for (int i = 0; i < fileNameLength * 8; i++)
            setbit((unsigned char *)fileName, i, getbit(encoding, i + encodingBitCnt + bitReadCnt));
        bitReadCnt += (fileNameLength * 8);

        fileSize = decode(encoding, encodingBitCnt + bitReadCnt);
        bitReadCnt += getNumOfBitsToEncode(fileSize);

        filePointer = decode(encoding, encodingBitCnt + bitReadCnt);
        bitReadCnt += getNumOfBitsToEncode(filePointer);
        if (isRemoved == 0)
        {
            if (strcmp(fileName, fileNameToRemove) == 0)
            {
                // Goto encoding to the bytenumber at (encodingBitCount/8)
                // set the bit 0 to 1
                setbit(encoding, encodingBitCnt, 1);
                // move the vdfp to the byteCnt + 32
                // write the byte there
                fseek(vdfp, byteCnt + 32, SEEK_SET);
                fwrite(encoding + (myCeilDiv(encodingBitCnt, 8)), 1, 1, vdfp);
                disk_state.fileCount--;
                updateDisksMetaData(vdfp);
                printf("File  removed. \n");
                return;
            }

            fileCnt--;
        }

        currPointerCnt++;

        if (fileCnt == 0)
            break;
        encodingBitCnt += myCeilDiv(bitReadCnt, 8) * 8;
        byteCnt += myCeilDiv(bitReadCnt, 8);
        if (currPointerCnt == maxPointersInBuffer)
        {
            fseek(vdfp, byteCnt + 32, SEEK_SET);
            printf("%ld\n", ftell(vdfp));
            fread(encoding, 1, MAX_BUFFER_SIZE, vdfp);
            currPointerCnt = 0;
            encodingBitCnt = 0;
        }
    }

    printf("File Not Found.\n");
}
