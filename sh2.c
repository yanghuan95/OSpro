/*************************************************************************
    > File Name: sh2.c
    > Author: yh
    > Mail: yanghuancoder@163.com 
    > Created Time: Sun 16 Apr 2017 06:35:56 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char *args[]){
	if(argc > 1){
		execvp(args[1], &args[1]);
	}else{
		char input[100];
		while(1){
			printf("sh2:");
			gets(input);
			if(strcmp(input, "exit") == 0){
				break;
			}
			int pid = fork();
			if(pid == 0){
				char *head, *tail;
				head = strtok(input, ">");
				tail = strtok(NULL, "");

				char *order = strtok(head, " ");
				char *left = strtok(NULL, "");
				if(tail == NULL){
					//there is no need to 
					//redirect
					int error = execlp(order, order, left, NULL);
				}else{
					char *file_name;
					if(tail[0] == ' '){
						file_name = &tail[1];
					}
					else{
						file_name = tail;
					}
					int file = open(file_name, O_CREAT|O_WRONLY);
					if(file < 0){
						perror("fail to open file");
					}
					for(int i = 0; i < strlen(left); ++i)
						write(file, &left[i], 1);
					char temp = '\n';
					write(file, &temp, 1);
					close(file);
				}
				exit(0);
			}
		}
	}

	return 0;
}
