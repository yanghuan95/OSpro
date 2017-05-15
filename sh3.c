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
#include<sys/wait.h>

int main(int argc, char *argv[]){
	
	if(argc > 1){
		execvp(argv[1], &argv[1]);
	}else{
		char input[100];
		int fd[2];

		int res = pipe(fd);	//create pipe

		if(res == -1){
			perror("Pipe error");
			exit(1);
		}

			fprintf(stdout, "sh3:");
			fgets(input, 100, stdin);
			
			if(strcmp(input, "exit") == 0){
				exit(0);
			}

			char *temp;
			char deal[100][100];
			int len = 0;
			
			temp = strtok(input, "|");

			do{
				int i = 0;
				for(; i < strlen(temp); ++i){
					if(temp[i] != ' '){
						break;
					}
				}
				strcpy(deal[len], &temp[i]);
				++len;
			}while((temp = strtok(NULL, "|")) != NULL);

			int pid = fork();

			if(pid > 0){
				close(fd[1]);
				dup2(fd[0], 0);
				execlp(deal[1], deal[1], (char *)0);
				wait(NULL);
			}else if(pid == 0){
				dup2(fd[1], 1);
				close(fd[0]);
				execlp(deal[0], deal[0], NULL);
				exit(0);
			}else{
				perror("fork error");
				exit(2);
			}
	}

	return 0;
}
