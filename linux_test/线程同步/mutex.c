#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int num = 0;
pthread_mutex_t mutex;  // 全局变量

void *count(void *arg) {
    int cnt = 1000;
    pthread_mutex_lock(&mutex);  // 加锁
    while (cnt--) {
        num++;
        usleep(1);
        printf("%d号tid: %lu 执行完毕\n", num, pthread_self());
    }
    pthread_mutex_unlock(&mutex);  // 解锁
    return 0;
}

int main() {
    pthread_t tid[10];
    pthread_mutex_init(&mutex, NULL);  // 初始化
    for (int i = 0; i < 10; i++) {
        int ret = pthread_create(tid + i, NULL, count, (void *)&num);
        if (ret != 0) printf("pthread_create: %s\n", strerror(ret));
    }
    for (int i = 0; i < 10; i++) {
        pthread_join(tid[i], NULL);
    }
    printf("num = %d\n", num);
    pthread_mutex_destroy(&mutex);  // 释放互斥锁资源
    return 0;
}