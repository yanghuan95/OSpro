/*************************************************************************
    > File Name: sh3.c
    > Author: yh
    > Mail: yanghuancoder@163.com 
    > Created Time: Mon 15 May 2017 05:02:13 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

static int in_temp;
static int out_temp;

void deal(char *);
void dealWriteSingle(char *, int *fd);
void dealReadSingle(char *, int *fd);
void dealString(char *);
int hasPattern(char *, char);

int main(int argc, char *argv[]){
	if(argc > 1){
		execvp(argv[1], &argv[1]);
	}else{
		dup2(0, in_temp);
		dup2(1, out_temp);
		while(1){
			printf("sh3:");
			dup2(in_temp, 0);
			dup2(out_temp, 1);
			char user_input[100];
			memset(user_input, 0, sizeof(user_input));
			fgets(user_input, sizeof(user_input), stdin);
			deal(user_input);
			wait(NULL);
			fflush(stdin);
			fflush(stdout);
		}
	}
}	

void deal(char *user_input){
	
	char array[20][100];
	int len = 0;

	char *temp = strtok(user_input, "|");
	int index = 0;
	for(; index < strlen(temp); ++index){
		if(temp[index] != ' ')
			break;
	}
	strncpy(array[len++], &temp[index], strlen(temp));
	while((temp = strtok(NULL, "|")) != NULL){
		for(index = 0; index < strlen(temp); ++index){
			if(temp[index] != ' ')
				break;
		}
		strncpy(array[len++], &temp[index], strlen(temp));
	}
	
	int i = 0;
	while(i < len){
		int fd[2];
		pipe(fd);

		int pid;
		if((pid = fork()) < 0){
			perror("error in fork");
		}

		if(pid == 0){
			dealWriteSingle(array[i++], fd);
		}
		dealReadSingle(array[i++], fd);
	}

}

void dealWriteSingle(char *input, int *fd){
	char temp[20][100];
	int len;
	int index;
	if((index = hasPattern(input, '<')) != -1){
		for(; index < strlen(input); ++index){
			if(input[index] != ' ')
				break;
		}
		char *file_name = &input[index];
		fd[0] = open(file_name, O_WRONLY|O_CREAT);

		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}else if((index = hasPattern(input, '>')) != -1){
		for(; index < strlen(input); ++index){
			if(input[index] != ' ')
				break;
		}
		char *file_name = &input[index];
		fd[1] = open(file_name, O_wRONLY|O_CREAT);

		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}else{
		dealString(input);
	}

}

void dealReadSingle(char *input, int *fd){
	int index;
	if((index = hasPattern(input, '<')) != -1){
		for(; index < strlen(input); ++index){
			if(input[index] != ' ')
				break;
		}
		char *file_name = &input[index];
		fd[0] = open(file_name, O_RDONLY|O_CREAT);

		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
	}else if((index = hasPattern(input, '>')) != -1){
		for(; index < strlen(input); ++index){
			if(input[index] != ' ')
				break;
		}
		char *file_name = &input[index];
		fd[1] = open(file_name, O_RDONLY|O_CREAT);

		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
	}else{
		dealString(input);
	}

}

void dealString(char *str){
	char *temp[100];
	int len = 0;
	temp[len] = (char *)malloc(100 * sizeof(char));
	char *mp = strtok(str, " ");
	if(mp != NULL){
		strncpy(temp[len++], mp, strlen(mp));
		temp[len] = (char *)malloc(100 * sizeof(char));
	}
	while((mp = strtok(NULL, " ")) != NULL){
		strncpy(temp[len++], mp, strlen(mp));
		temp[len] = (char *)malloc(100 * sizeof(char));
	}

	temp[len++] = (char *)malloc(100 * sizeof(char));
	temp[len++] = NULL;
	
	execvp(temp[0], temp);
}

int hasPattern(char *str, char pattern){
	int i = 0;
	int index = -1;
	for(; i < strlen(str); ++i){
		if(str[i] == pattern){
			index = i;
			break;
		}
	}
	return index;
}
