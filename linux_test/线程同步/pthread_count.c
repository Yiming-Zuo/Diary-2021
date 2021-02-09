#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int num = 0;

void *count(void *arg) {
    int cnt = 100;
    while (cnt--) {
        num++;
        usleep(100);
        printf("%d号tid: %lu 执行完毕\n", num, pthread_self());
    }
    
    return 0;
}

int main() {
    pthread_t tid[10];
    for (int i = 0; i < 10; i++) {
        int ret = pthread_create(tid + i, NULL, count, (void *)&num);
        if (ret != 0) printf("pthread_create: %s\n", strerror(ret));
    }
    for (int i = 0; i < 10; i++) {
        pthread_join(tid[i], NULL);
    }
    printf("num = %d\n", num);
    return 0;
}