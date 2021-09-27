#include<stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int n = 0;

    scanf("%d", &n);

    for(int i = 0; i < n; i++){

        if(fork() == 0){
            printf("[son] pid %d from [parent] pid %d\n", getpid(), getppid());
            exit(0);
        }
    }

    for(int i = 0; i < n; i++)
    wait(NULL);
} 
