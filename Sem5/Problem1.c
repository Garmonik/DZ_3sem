#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

#define BUF_SIZE 4096

int num_client(char* name1, char* name2);

int main(int argc, char** argv){
    
    if(strcmp(argv[1], "0") == 0)
        num_client("aaa.fifo", "bbb.fifo");
    else if(strcmp(argv[1], "1") == 0)
        num_client("bbb.fifo", "aaa.fifo");
            
    return 0;
}

int num_client(char* name1, char* name2){    
    int fd;
    size_t size;
    char* resstring;
    char* str;
    
    resstring = (char*)calloc(BUF_SIZE, sizeof(char));
    str = (char*)calloc(BUF_SIZE, sizeof(char));
    
    (void)umask;
    
    pid_t mass_fork = fork();
    
    mknod(name1, S_IFIFO|0666, 0);

    if(mass_fork < 0){
         printf("Error1!");
         exit(-1);
    }
    else if(mass_fork > 0){ 
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
     
            printf("%s", resstring);
            }
            close(fd);
    }
    free(str);
    free(resstring);

    return 0;
}
