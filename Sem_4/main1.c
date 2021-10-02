#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv){
 
    int fd1 = 0;
    char* arr = NULL;
        
    arr = (char*)calloc(4048, sizeof(char));
 
    fd1 = open(argv[1], O_RDONLY);

    int n = read(fd1, arr, 256);
    while(n != 0){
        write(1, arr,  n);
        n = read(fd1, arr, 256);
    }
    free(arr);    
    close(fd1);
     return 0;
 }

