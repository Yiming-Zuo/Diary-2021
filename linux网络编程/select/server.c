#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>

int main() {
    // 创建 lfd
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1) {
        perror("socket");
        exit(0);
    }
    // bind
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3333);
    addr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(lfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1) {
        perror("bind");
        exit(0);
    }
    // listen
    ret = listen(lfd, 100);
    if (ret == -1) {
        perror("listen");
        exit(0);
    }
    printf("等待连接...\n");
    // select
    // 委托内核检测读缓冲区是否有变化 - lfd/connfd

    // fd_set初始化
    fd_set rdset, tmp;
    FD_ZERO(&rdset);
    FD_SET(lfd, &rdset);
    int maxfd = lfd;

    while (1) {
        // 委托内核检测lfd读缓冲区是否有变化
        tmp = rdset;
        ret = select(maxfd + 1, &tmp, NULL, NULL, NULL);
        if (ret == -1) {
            perror("select");
            exit(0);
        }
        // 有新连接 -> 建立连接，监测新连接的读缓冲区
        if (FD_ISSET(lfd, &tmp)) {  // 检测tmp
            // 接受新连接
            struct sockaddr_in addrCli;
            int len = sizeof(addrCli);
            int connfd = accept(lfd, (struct sockaddr *)&addrCli, &len);  // 不阻塞
            printf("%d 已连接\n", connfd);
            // 委托内核检测connfd的读缓冲区
            FD_SET(connfd, &rdset);  // 新连接放进rdset中
            maxfd = connfd > maxfd ? connfd : maxfd;
        }
        // connfd读缓冲区有变化 -> 通信
        for (int i = lfd + 1; i <= maxfd; i++) {
            // 缓冲区有数据
            if (FD_ISSET(i, &tmp)) {
                char buf[128];
                int ret = read(i, buf, sizeof(buf));
                if (ret == -1) {
                    perror("read");
                    exit(0);
                }
                else if(ret == 0) {
                    printf("%d已经关闭连接\n", i);
                    FD_CLR(i, &rdset);
                    close(i);
                } else {
                    printf("%d: %s\n", i, buf);
                    char sendBuf[256];
                    sprintf(sendBuf, "收到: %s\n", buf);
                    write(i, sendBuf, strlen(sendBuf) + 1);
                }
            }
        }
    }
    close(lfd);
    return 0;
}