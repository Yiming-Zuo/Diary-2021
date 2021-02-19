#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>

void printTime(int num) {
        time_t newTime;
        struct tm *timeInfo;
        time(&newTime);
        timeInfo = localtime(&newTime);
        // 写到文件的过程放在处理函数中
        int fd = open("./time.txt", O_WRONLY | O_CREAT | O_APPEND,  0664);
        if (fd == -1) perror("open");
        // printf("当前时间: %4d年%02d月%02d日 %02d:%02d:%02d\n", 1900+timeInfo->tm_year, 1+timeInfo->tm_mon, timeInfo->tm_mday, timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
        char *curTime = asctime(timeInfo);
        write(fd, curTime, strlen(curTime));
        // printf("%s\n", curTime);
        close(fd);
}

int main() {
    pid_t pid = fork();
    if (pid > 0) exit(0);
    else {
        // 提升为会话，脱离终端，后台运行
        setsid();
        printf("pid: %d\n", getpid());
        // 切换目录
        chdir("/Users/zuoyiming");
        // 修改掩码
        umask(022);  // 默认权限755
        // dup2(fd, 1); 重定向
        // dup2(fd, STDOUT_FILENO);
        int fd = open("/dev/null", O_RDWR);
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        // 核心操作
        // 信号捕捉
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = printTime;
        sigaction(SIGALRM, &act, NULL);
        // 定时器
        struct itimerval setTime;
        setTime.it_interval.tv_usec = 0;
        setTime.it_interval.tv_sec = 2;
        setTime.it_value.tv_usec = 0;
        setTime.it_value.tv_sec = 3;
        setitimer(ITIMER_REAL, &setTime, NULL);
        while (1) {}
    }
    return 0;
}