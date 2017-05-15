/*************************************************************************
    > File Name: sh3.c
    > Author: yh
    > Mail: yanghuancoder@163.com 
    > Created Time: Sun 07 May 2017 06:28:55 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>

void dealString(char *);

int main(){
	while(1){
		printf("sh3:");
		char user_input[100] = {0};
		fgets(user_input, sizeof(user_input), stdin);
		user_input[strlen(user_input) - 1] = 0;
		dealString(user_input);
	}
	return 0;
}

void dealString(char *input){
	char * params[100];
	char *temp;
	char get[100];
	strcpy(get, input);
	int i = 0;
	int j = 0;
		
	for(; j < 20; ++j){
		params[j] = (char *) malloc(sizeof(char) * 100);
	}

	temp = strtok(get, " ");
	strcpy(params[i++], temp);
	if(strcmp(temp, input) != 0){
		while((temp = strtok(NULL, " ")) != NULL){
			strcpy(params[i++], temp);
		}
	}

	params[i] = NULL;
	int error = execvp(params[0], params);
	if(error < 0){
		perror("bad express");
	}
}
