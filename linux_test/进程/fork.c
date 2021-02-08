#include <stdio.h>
#include <unistd.h>

int main() {
    int n = 10;
    printf("主进程号pid: %d\n", getpid());
    pid_t pid = fork();
    if (pid > 0) {
        printf("父进程的返回值: %d\n", pid);
        printf("父进程pid: %d\n", getpid());
        printf("父进程ppid: %d\n", getppid());
        printf("父进程n值修改前: %d\n", n);
        n += 10;
        printf("父进程n值修改后: %d\n", n);
    } else
    {
        printf("子进程的返回值: %d\n", pid);
        printf("子进程pid: %d\n", getpid());
        printf("子进程ppid: %d\n", getppid());
        printf("子进程n值修改前: %d\n", n);
        n += 100;
        printf("子进程n值修改后: %d\n", n);
    }
    for ( int i = 0; i < 3; i++ ) {
        printf("i = %d\n", i);
    }
    return 0;
}

/*
主进程号pid: 17723
父进程的返回值: 17724
父进程pid: 17723
父进程ppid: 16419
父进程n值修改前: 10
父进程n值修改后: 20
i = 0
i = 1
i = 2
子进程的返回值: 0
子进程pid: 17724
子进程ppid: 1
子进程n值修改前: 10
子进程n值修改后: 110
i = 0
i = 1
i = 2
*/