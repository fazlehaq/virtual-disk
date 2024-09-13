#include<stdio.h>
#include"file_utils.h"
#include<sys/stat.h>
#include"types.h"
#include"constants.h"

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
void copyfile(FILE *src, FILE *dest)
 {
        unsigned char buffer[MAX_BUFFER_SIZE];
        size_t bytes;

        // bytes stores the number of bytes read by fread function 
        while( (bytes = fread(buffer,1,sizeof(buffer),src)) > 0 ){
                fwrite(buffer,1,bytes,dest);
        }

}