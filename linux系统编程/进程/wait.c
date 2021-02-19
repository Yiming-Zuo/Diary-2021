#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int waitTest() {
    pid_t pid;
    for (int i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) break;
    }
    if (pid > 0) {
        while (1) {
            printf("parent, pid = %d\n", getpid());
            int s;
            int ret = wait(&s);  // 父进程还有子进程时，堵塞
            if (ret == -1) break;
            if (WIFEXITED(s)) {  // 正常退出
                printf("pid:%d 正常退出，退出码: %d\n", ret, WEXITSTATUS(s));
            } else if (WIFSIGNALED(s))  // 被信号干掉
            {
                printf("pid:%d 被信号%d干掉了\n", ret, WTERMSIG(s));
            }
            
        }
    } else {
        printf("child, pid = %d\n", getpid());
        while(1) {}
    }
    return 0;
}

void waitpidTest() {
    pid_t pid;
    for (int i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) break;
    }
    if (pid > 0) {
        while (1) {
            int s;
            int ret = waitpid(-1, &s, WNOHANG);
            if (ret > 0) {
                if (WIFEXITED(s)) {
                    printf("pid:%d 正常退出，退出码: %d\n", ret, WEXITSTATUS(s));
                }
                if (WIFSIGNALED(s)) {
                    printf("pid:%d 被信号%d干掉了\n", ret, WTERMSIG(s));
                }
            } else if (ret == 0) {
                // printf("还有子进程正在运行");
            } else {
                printf("子进程全部回收");
            } 
        }
    } else if (pid == 0) {
            printf("child, pid = %d\n", getpid());
            while(1) {}
        }
}

int main () {
    waitpidTest();
    return 0;
}