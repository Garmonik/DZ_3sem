#include<stdio.h>
#include<string.h>
#include<assert.h>

#define BUF_SIZE 4096

void Split(char* str, char* sep);

int main(int argc, char **argv){

    char str[BUF_SIZE] = "";
    char sep[2] = "";

    fgets (str, BUF_SIZE, stdin);
	scanf("%c", sep);

    Split(str, sep);
	return 0;
}

void Split(char* str, char* sep){

    char* tmp = strtok(str, sep);
    while (tmp != NULL){ 
        printf("%s\n", tmp);
        tmp = strtok (NULL, sep); 
    }
}


//fferrette
//ff rr tt 
