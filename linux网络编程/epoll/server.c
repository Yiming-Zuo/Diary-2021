#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

int main() {
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1) {
        perror("socket");
        exit(0);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 3333;
    addr.sin_addr.s_addr = INADDR_ANY;
    socklen_t len = sizeof(addr);
    int ret = bind(lfd, (struct sockaddr *)&addr, &len);
    if (ret == -1) {
        perror("bind");
        exit(0);
    }
    ret = listen(lfd, 100);
    printf("等待连接...\n")
    if (ret == -1) {
        perror("listen");
        exit(0);
    }
    // 创建epoll树
    int epfd = epoll_create(1000);
    if (epfd == -1) {
        perror("epoll_create");
        exit(0);
    }
    // 监听lfd结点添加到树上
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = lfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);

    struct epoll_event evs[1000];
    while (1) { 
        int ret = epoll_wait(epfd, evs, 1000, -1);
        if (ret) {
            for (int i = 0; i < ret; i++) {
                if (evs[i].data.fd = lfd) {
                    int connfd = accept(lfd, NULL, NULL);
                    if (connfd == -1) {
                        perror("accept");
                        exit(0);
                    }
                    printf("%d 已连接\n"， evs[i].data.fd);
                    // 将通信的新fd添加到树上
                    struct epoll_event connev;
                    connev.events = EPOLLIN;
                    connev.data.fd = connfd;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &connev);
                } else {
                    char buf[128];
                    int ret = read(evs[i].data.fd, buf, sizeof(buf));
                    if (ret == -1) {
                        perror("read");
                        exit(0);
                    } else if (ret == 0)
                    {
                        printf("%i 断开连接\n", evs[i].data.fd)
                        // 从树上删除结点
                        epoll_ctl(epfd, EPOLL_CTL_DEL, evs[i].data.fd, NULL);
                        close(evs[i].data.fd);
                    } else {
                        printf("%d : %s\n", evs[i].data.fd, buf);
                        char *sendbuf[256];
                        sprint(sendbuf, "收到: %s\n", buf);
                        write(evs[i].data.fd, sendbuf, strlen(sendbuf));
                    }
                }
            }
        }
    }
    close(lfd);
}