#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main() {
    // 创建信号集
    sigset_t set;
    // 清空信号集
    sigemptyset(&set);
    // 设置堵塞
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);
    // 添加到内核
    sigprocmask(SIG_BLOCK, &set, NULL);
    int count = 0;
    while (1) {
        sigset_t pend;
        // 读取未决信号集
        sigpending(&pend);
        // 遍历标志位
        for (int i = 0; i < 31; i++) {
            int ret = sigismember(&pend, i+1);
            if (ret == -1) {
                perror("sigismember");
                exit(-1);
            }
            printf("%d ", ret);
        }
        printf("\n");
        count++;
        if (count == 10) {
            sigprocmask(SIG_UNBLOCK, &set, NULL);
            break;
        }
    }
    return 0;
}