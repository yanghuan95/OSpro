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

int stdin_temp, stdout_temp;

void dealInput(char *);
void dealString(char *);

int main(){
	while(1){
		printf("sh3:");
		char user_input[100] = {0};
		fgets(user_input, sizeof(user_input), stdin);
		user_input[strlen(user_input) - 1] = 0;
		dup2(0, stdin_temp);
		dup2(1, stdout_temp);
		dealInput(user_input);
		dup2(stdin_temp, 0);
		dup2(stdout_temp, 1);
	}
	return 0;
}

void dealInput(char *input){
	char * params[100];
	char *temp;
	char get[100];
	strcpy(get, input);
	int i = 0;
	int j = 0;
		
	for(; j < 20; ++j){
		params[j] = (char *) malloc(sizeof(char) * 100);
	}

	temp = strtok(get, "|");
	for(j = 0; j < strlen(temp); ++j){
		if(temp[j] != ' ')
			break;
	}
	strncpy(params[i++], &temp[j], strlen(temp));
	if(strcmp(temp, input) != 0){
		while((temp = strtok(NULL, "|")) != NULL){
			for(j = 0; j < strlen(temp); ++j){
				if(temp[j] != ' ')
					break;
			}
			strncpy(params[i++], &temp[j], strlen(temp));
		}

		int pip_num = i-1;
		j = 0;
		int pip_fd;
		if((pip_fd = fork()) == 0){

			int fd[2], res;
			pid_t pid;
			res = pipe(fd);
			if(res == -1) {
				perror("Pipe error!");
				exit(1);
			}
			pid = fork();
			if(pid > 0) {
				dup2(fd[0], 0);
				close(fd[0]);
				close(fd[1]);
				dealString(params[i-1]);
				wait(NULL);
				i += 2;
			} else if(pid == 0) {
				int po = 0;
				while(po < pip_num){
					int load = fork();
					if(load == 0){
						dup2(fd[1], 1);
						close(fd[0]);
						close(fd[1]);
						dealString(params[po]);
						exit(0);
					}
					wait(NULL);
					++po;
				}
				exit(0);
			} else {
				perror("Fork error!");
				exit(2);
			}
	
			exit(0);
		}
		wait(NULL);
	}else{
		dealString(input);
	}
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
