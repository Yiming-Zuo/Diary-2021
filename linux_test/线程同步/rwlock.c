#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
 
int num = 0;
pthread_rwlock_t rwlock;

void *myRead(void *arg) {
    pthread_rwlock_rdlock(&rwlock);
    int count = 1000;
    while (count--) {
        printf("%ld read num = %d\n", pthread_self(), num);
        usleep(100);
    }
    pthread_rwlock_rdlock(&rwlock);
    return 0;
}

void *myWrite(void *arg) {
    pthread_rwlock_wrlock(&rwlock);
    int count = 1000;
    while (count--) {
        num++;
        usleep(1000);
        printf("%ld write num++ = %d\n", pthread_self(), num);
    }
    pthread_rwlock_unlock(&rwlock);
    return 0;
}

int main() {
    pthread_t wtid[3], rtid[5];
    pthread_rwlock_init(&rwlock, NULL);
    for (int i = 0; i < 3; i++) {
        pthread_create(wtid+i, NULL, myWrite, NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_create(rtid+i, NULL, myRead, NULL);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(wtid[i], NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(rtid[i], NULL);
    }
    pthread_rwlock_destroy(&rwlock);
    printf("num = %d\n", num);
    return 0;
}