#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
int main()
{
    int fd[2], res;
    pid_t pid;
    res = pipe(fd);
    if(res == -1) {
        perror("Pipe error!");
        exit(1);
    }
    pid = fork();
    if(pid > 0) {
        close(fd[1]);
        dup2(fd[0], 0);
        execl("/usr/bin/sort", "sort", (char *)0);
        wait(NULL);
        exit(0);
    } else if(pid == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        execl("/bin/cat", "cat", "input.txt", NULL);
        exit(0);
    } else {
        perror("Fork error!");
        exit(2);
    }
}
