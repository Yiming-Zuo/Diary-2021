#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

// 读数据
int main() {
    // 打开管道
    int fd = open("test", O_RDONLY);
    // 读数据
    while (1) {
        char buf[1024];
        read(fd, buf, sizeof(buf));
        printf("%s", buf);
    }
    // 关闭管道
    close(fd);

    return 0;
}