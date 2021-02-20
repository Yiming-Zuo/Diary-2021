#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    // 1 scoket
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(0);
    }
    // 2 connect
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3333);
    addr.sin_addr.s_addr = INADDR_ANY;
    int ret = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1) {
        perror("connect");
        exit(0);
    }
    printf("连接成功\n");
    // 1 write+read
    while (1) {
        char sendBuf[1024];
        // printf("请输入:");
        // scanf("%s", sendBuf);  // 阻塞
        fgets(sendBuf, sizeof(sendBuf), stdin);
        write(fd, sendBuf, strlen(sendBuf)+1);
        char recvBuf[1024];
        int num = read(fd, recvBuf, sizeof(recvBuf));  // 阻塞
        printf("recv buf: ");
        write(STDOUT_FILENO, recvBuf, num);
    }
    close(fd);
    return 0;
}