#include<stdio.h>
#include<string.h>
#include<assert.h>

#define BUF_SIZE 4096

int main(int argc, char **argv){

/*	char* str = *(argv + 1);
	char* sep = *(argv + 2);*/

    char str[BUF_SIZE] = "";
    char sep[2] = "";
	int i = 0;
	char* res = NULL;

    fgets (str, BUF_SIZE, stdin);
	scanf("%c", sep);

    char* tmp = strtok(str, sep);
	
	while (tmp != NULL){
	    
        printf("%s\n", tmp);
//		res[i] = * tmp;
//		i++;
		tmp = strtok (NULL,sep);
	}
	return 0;
}
