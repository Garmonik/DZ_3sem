#include<stdio.h>
#include<string.h>
#include<assert.h>

#define BUF_SIZE 4096

void Split(char* str, char* sep, char** result);

int print_Split(char **str);

int main(){

    char str[BUF_SIZE] = "";
    char sep[2] = "";
    char* result[BUF_SIZE + 1] = {};

    fgets (str, BUF_SIZE, stdin);
	scanf("%c", sep);

    Split(str, sep, result);
    print_Split(result);

	return 0;
}

void Split(char* str, char* sep, char** result){
    
    assert(str);
    assert(result);
    assert(sep);

    int i = 0;
    char* tmp = strtok(str, sep);
    while (tmp != NULL){ 
        result[i] = tmp;
        i++;
        tmp = strtok (NULL, sep); 
    }
}

int print_Split(char **str){
        assert (str);

        for(; *str != NULL; str++)
            printf ("%s\n", *str);

        return 0;
}

//fferrette
//ff rr tt 
