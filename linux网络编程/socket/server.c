#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    // 1 socket
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(0);
    }
    // 2 bind
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3333);
    // inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
    addr.sin_addr.s_addr = INADDR_ANY; // 内核获取IP
    int ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1) {
        perror("bind");
        exit(0);
    }
    // 3 listen
    ret = listen(fd, 100);
        if (ret == -1) {
        perror("listen");
        exit(0);
    }
    printf("等待连接...\n");

    // 4 accept
    struct sockaddr_in addrCli;
    int addrLen = sizeof(addrCli);
    int connfd = accept(fd, (struct sockaddr *)&addrCli, (socklen_t *)&addrLen);  // 阻塞
    if (connfd == -1) {
        perror("accept");
        exit(0);
    }
    printf("连接成功...\n");
    // 打印客户端信息
    char ip[32];
    inet_ntop(AF_INET, &addrCli.sin_addr.s_addr, ip, sizeof(ip));
    printf("Client IP: %s, Port %d\n", ip, ntohs(addrCli.sin_port));

    // 5 read+wirte
    while (1) {
        char recvBuf[1024];
        int ret = read(connfd, recvBuf, sizeof(recvBuf));  // 阻塞
        if (ret == -1) {
            perror("read");
            break;
        } else if (ret == 0) {
            printf("连接断开\n");
            break;
        } else {
            printf("recv buf: %s\n", recvBuf);
            char *sendBuf = "收到\n";
            write(connfd, sendBuf, strlen(sendBuf)+1);
        }

    }

    close(fd);
    close(connfd);

    return 0;
}