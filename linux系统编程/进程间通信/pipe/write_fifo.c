#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

// 写数据
int main() {
    // 创建有名管道
    int ret = mkfifo("test", 0664);
    if (ret == -1) {
        perror("mkfifo");
        exit(0);
    }
    // 打开管道
    int fd = open("test", O_WRONLY);
    // 写数据
    for (int i = 0; i < 100; i++) {
        char buf[1024];
        sprintf(buf, "hello, %d\n", i);
        write(fd, buf, strlen(buf));
    }
    // 关闭管道
    close(fd);

    return 0;
}