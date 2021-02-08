#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void recycle(int num) {
    printf("捕捉到信号%d\n", num);
    while (1) {
        // wait(NULL);  // 堵塞
        int ret = waitpid(-1, NULL, WNOHANG);
        if (ret > 0) {
            printf("回收子进程%d\n", ret);
        } else if (ret == -1) {
            printf("所有子进程都死了，回收完毕");
            break;
        } else if (ret == 0) {
            break;  // 死掉的进程回收完毕，如果一直未死的子进程，不会阻塞
        }
    }
}

int main() {
    // 设置信号阻塞，子进程如果在主进程捕捉信号之前死掉不会接受到SIGCHLD忽略
    // 在主进程捕捉信号语句之后接触堵塞，主进程接受到信号进行处理
    // 解决所有子线程如果在信号捕捉语句之前全部死掉
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);
    // 创建子进程后阻塞集会复制到子进程地址空间
    pid_t pid;
    for (int i = 0; i < 20; i++) {
        pid = fork();
        if (pid == 0) {
            break;
        }
    }
    if (pid > 0) {
        // signal(SIGCHLD, recycle);
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = recycle;
        sigemptyset(&act.sa_mask);
        // signal(SIGCHLD, recycle);  // 不阻塞
        sigaction(SIGCHLD, &act, NULL);  // 捕捉信号, 不阻塞，可能20个信号一起捕捉到
        sigprocmask(SIG_UNBLOCK, &set, NULL);  // 解除阻塞
        while (1) {
            sleep(3);
        }
    } else {
        printf("1");
    }
    return 0;
}