#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void func(int num) {
        printf("捕捉到了%d\n", num);
    }
int main() {
    struct itimerval newVal;
    newVal.it_interval.tv_usec = 0;
    newVal.it_interval.tv_sec = 3;
    newVal.it_value.tv_usec = 0;
    newVal.it_value.tv_sec = 5;
    setitimer(ITIMER_REAL, &newVal, NULL);
    // 捕捉信号
    while (1) {
        signal(SIGALRM, func);
        signal(2, func);
    }
    return 0;
}