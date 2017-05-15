/*************************************************************************
    > File Name: mysys.c
    > Author: zll
    > Mail: zhnllion@126.com 
    > Created Time: Sun 09 Apr 2017 06:03:13 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

void mysys(char *input);

int main(int argc, char *argv[]){
	char input[100];
	if(argc == 1){
		printf("please enter a params to use mysys\n");
		gets(input);
		mysys(input);
	}else{
		int i = 1;
		for(; i < argc; ++i){
			strcat(input, " ");
			strcat(input, argv[i]);
		}
		mysys(input);
	}
	return 0;
}

void mysys(char *input){
	char *request = NULL;
	request = strtok(input, " ");
	int error;
	char *temp = strtok(NULL, "");
	if(temp == NULL){
		//that's mean that this is printf
		printf("%s\n", request);
	}
	else{
		error = execlp(request, request, temp, NULL);
		if(error < 0){
			perror("execlp");
		}
	}
}
