/*************************************************************************
    > File Name: sh1.c
    > Author: yh
    > Mail: yanghuancoder@163.com 
    > Created Time: Sun 16 Apr 2017 06:35:56 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *args[]){
	if(argc > 1){
		execvp(args[1], &args[1]);
	}else{
		char input[100];
		while(1){
			printf("sh1:");
			gets(input);
			if(strcmp(input, "exit") == 0){
				break;
			}
			int pid = fork();
			if(pid == 0){
				char * params[100];
				char *temp;
				int i = 0;
			
				for(int j = 0; j < 100; ++j){
					params[j] = (char *) malloc(sizeof(char) * 100);
				}

				temp = strtok(input, " ");
				while(temp != NULL){
					strcpy(params[i], temp);
					++i;
					temp = strtok(NULL, " ");
				}
				params[i] = NULL;
				int error = execvp(params[0], params);
				if(error < 0){
					perror("bad express");
				}
				
				break;
			}
		}
	}

	return 0;
}
