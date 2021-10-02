#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>

int main(){

    int pfd, c, b;
    int fd[2];
    char a[100];
    int size = 0;
    
    if((pfd = pipe(fd)) < 0){
        printf("Error");

        exit(1);
    }
    else{
        do{
            c = write(fd[1], "h", 2);
            b = read(fd[0], a, 1);
            size = size + 2;

            printf("%d\n", size);
        }
        while(c != b);
    }
    return 0;
}
