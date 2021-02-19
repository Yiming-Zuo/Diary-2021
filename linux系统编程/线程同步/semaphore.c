#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *head = NULL;
sem_t psem;
sem_t csem;
pthread_mutex_t mtx;

void *producer(void *arg) {
    int count = 10;
    while (count--) {
        sem_wait(&psem);  // psem--  if (psem = 0) 阻塞
        pthread_mutex_lock(&mtx);

        struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
        newNode->val = rand() % 1000;
        newNode->next = head;
        head = newNode;
        printf("ptid %lu 生产结点 %d\n", pthread_self(), head->val);

        pthread_mutex_unlock(&mtx);
        // 通知消费者
        sem_post(&csem);  // csem++  csem <= 6
    }
}

void *customer(void *arg) {
    int count = 10;
    while (count--) {
        int csem_val = sem_getvalue(&csem, &csem_val);
        printf("csem: %d\n", csem_val);
        sem_wait(&csem);  // csem--
        // 如果有多个线程进入，串行运行
        pthread_mutex_lock(&mtx);

        struct ListNode *tmp = head;
        head = head->next;
        printf("ctid %lu 消费结点 %d\n", pthread_self(), tmp->val);
        free(tmp);

        pthread_mutex_unlock(&mtx);
        sem_post(&psem);  // psem <= 8  放在互斥后解锁以后
    }
}

int main() {
    pthread_t ptid[5], ctid[5];
    pthread_mutex_init(&mtx, NULL);
    sem_init(&psem, 0, 8);
    sem_init(&csem, 0, 0);  // 消费者默认阻塞

    for (int i = 0; i < 5; i++) {
        pthread_create(ptid + i, NULL, producer, NULL);
        pthread_create(ctid + i, NULL, customer, NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(ptid[i], NULL);
        pthread_join(ctid[i], NULL);
    }
    
    sem_destroy(&psem);
    sem_destroy(&csem);
    pthread_mutex_destroy(&mtx);
    return 0;

}