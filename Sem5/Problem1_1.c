#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

#define BUF_SIZE 4096

int main(){

    int fd;
    size_t size;
    char* resstring;
    char name1[] = "bbb.fifo";
    char name2[] = "aaa.fifo";
    char* str;

    resstring = (char*)calloc(BUF_SIZE, sizeof(char));
    str = (char*)calloc(BUF_SIZE, sizeof(char));

    (void)umask;

    if(mknod(name1, S_IFIFO|0666, 0) < 0){
    }
    if(fork() < 0){
        printf("Error1!");
        exit(-1);
    }
    else if(fork() > 0){
        fd = open(name1, O_WRONLY);

        if(fd < 0){
            printf("Error2!");
            exit(-1);
        }

            while(1){
                fgets(str, BUF_SIZE, stdin);

                int n = strlen(str);
                write(fd, str, n);
            }
    close(fd);
    }
    else{
        if((fd = open(name2, O_RDONLY)) < 0){
            printf("Error3!");
            exit(-1);
        }

        while(1){
            size = read(fd, resstring, BUF_SIZE);

            printf("%s\n", resstring);
            }
            close(fd);
   }
    return 0;
    free(str);
    free(resstring);
}
