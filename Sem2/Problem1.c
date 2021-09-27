#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

void GenerateString(int n, char *string);

int main(){
	int n = 0;

	scanf("%d", &n);

	char *string = (char*) malloc(sizeof(char)*(2<<(n+1)-1));
	string[0] = 'a';
	GenerateString(n, string);
	free(string);
}

void GenerateString(int n, char *string){
	int len = 1;
	for(int i = 0; i < n; i++){
		string[len] = 'a' + i + 1;
		strncpy(string+len+1, string, len);
		len = 2*len + 1;
	}
		printf("%s\n", string);
}
