#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (){

    
    if (fork() == 0)
        execlp ("gcc", "gcc", "HelloWorld.c", "-o", "prog", NULL);
    if (fork() < 0)
        exit(-1);
    else if (fork() > 0){
        execlp ("./prog", "./prog",  NULL);

    printf ("Error\n");
}
    return 0;
}
