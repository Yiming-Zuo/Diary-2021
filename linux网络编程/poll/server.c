#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/poll.h>

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
    // poll
    // 委托内核检测读缓冲区是否有变化 - lfd/connfd

    // pollfd初始化
    struct pollfd fds[100];
    int nfds = 0;
    fds[nfds].fd = lfd;
    fds[nfds].events = POLLIN;
    nfds++;


    while (1) {
        int n = poll(fds, nfds, -1);
        if (n == -1) {
            perror("poll");
            exit(0);
        }

        for (int i = 0; i < nfds; i++) {
            if (fds[i].revents & POLLIN) {
                // lfd有变化 -> 建立连接，添加进fds中
                if (i == 0) {
                    struct sockaddr_in sockcli;
                    int len = sizeof(sockcli);      
                    int connfd = accept(lfd, (struct sockaddr *)&sockcli, &len);
                    fds[nfds].fd = connfd;
                    fds[nfds].events = POLLIN;
                    printf("%d已连接\n", fds[nfds].fd);
                    nfds++;
                } else {
                    // 通信
                    char buf[128];
                    int ret = read(fds[i].fd, buf, sizeof(buf));
                    if (ret == -1) {
                        perror("read");
                        exit(0);
                    } else if (ret == 0) {
                        printf("%d断开连接\n", fds[i].fd);
                        close(fds[i].fd);
                    } else {
                        printf("%d: %s\n", fds[i].fd, buf);
                        char sendBuf[256];
                        sprintf(sendBuf, "收到: %s\n", buf);
                        write(fds[i].fd, sendBuf, strlen(sendBuf) + 1);
                    }
                }
            }
        }


    }
    close(lfd);
    return 0;
}