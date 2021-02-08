#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int fd[2];
    int ret = pipe(fd);  // 创建匿名管道：内存缓冲区
    if (ret == -1) {
        perror("pipe");
        exit(0);
    }
    pid = fork();
    if (pid > 0) {  // 读管道
        char buf[1024];
        read(fd[0], buf, sizeof(buf));  // 堵塞
        printf("%s", buf);
        wait(NULL);
    }
    else if (pid == 0) {  // 写管道
        dup2(fd[1], STDOUT_FILENO);  // 文件描述符重定向，标准输出描述符重定向为fd[1]
        execlp("ps", "ps", "aux", NULL);  // 默认输出到终端中，只能写4k
        perror("execlp");  // 如果执行到这，说明execlp失败
        exit(0);
    } else {
        perror("fork");
    }
    return 0;
}