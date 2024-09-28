#include<stdio.h>
#include<sys/stat.h>
#include"../headers/file_utils.h"
#include"../headers/types.h"
#include"../headers/constants.h"

/// @brief Takes the name/path of the file and return its size
/// @return the total size of file in the bytes
ull getFileSize(char *name){
    struct stat fileStat;
    if (stat(name,&fileStat) == 0){
            return (long long)fileStat.st_size;
    }
    perror("stat");
    return 0;
}

/// @brief Copies one file into another
/// @param src File pointer of the source file
/// @param dest File pointer of the destination file 
/// @param size Either null or some positive value representing number of bytes to copy from src to dest
void copyfile(FILE *src, FILE *dest,ull size){
        unsigned char buffer[MAX_BUFFER_SIZE];

        if(size == 0){
                int bytes;
                // bytes stores the number of bytes read by fread function 
                while( (bytes = fread(buffer,1,sizeof(buffer),src)) > 0 ){
                        fwrite(buffer,1,bytes,dest);
                }
        }

        else{
                ull remaining_bytes = size;

                while (remaining_bytes > MAX_BUFFER_SIZE){
                        fread(buffer,1,MAX_BUFFER_SIZE,src);
                        fwrite(buffer,1,MAX_BUFFER_SIZE,dest);
                        remaining_bytes -= MAX_BUFFER_SIZE;
                }

                if(remaining_bytes > 0){
                        fread(buffer,remaining_bytes,1,src);
                        fwrite(buffer,remaining_bytes,1,dest);
                }
        }

}