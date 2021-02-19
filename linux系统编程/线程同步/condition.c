#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *head = NULL;
pthread_cond_t cond;  // 任务队列空时，消费着阻塞
pthread_mutex_t mtx;  // 解决数据混乱：多个消费者同时消费一个结点

void *producer(void *arg) {
    int count = 10;
    while (count--) {
        pthread_mutex_lock(&mtx);
        struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
        newNode->val = rand() % 1000;
        newNode->next = head;
        head = newNode;
        printf("ptid %lu 生产结点 %d\n", pthread_self(), head->val);
        pthread_cond_signal(&cond);  // 通知cond解除阻塞
        pthread_mutex_unlock(&mtx);
    }
}

void *customer(void *arg) {
    int count = 10;
    while (count--) {
        pthread_mutex_lock(&mtx);
        /* 为什么用while?
        如果用if：segmentation fault
            有多个ctid阻塞在cond上 -> producer生产一个，cond解除阻塞 -> 多个ctid继续运行 -> 一个ctid抢到了mtx进行消费后释放mtx
                                                                                  -> 其它ctid阻塞                    -> 其它ctid抢到mtx后head为空 -> segmentation fault
        while：
            有多个ctid阻塞在cond上 -> producer生产一个，cond解除阻塞 -> 一个ctid抢到了mtx -> head != NULL -> 消费后释放mtx
                                                                -> 其它ctid阻塞                                      -> 其它ctid抢到mtx -> head == NULL -> cond阻塞，等待生产。
        */
        while (head == NULL) pthread_cond_wait(&cond, &mtx);  // 如果线程阻塞在了这，函数会给互斥锁解锁，cond解除阻塞后会给互斥锁加锁
        struct ListNode *tmp = head;
        head = head->next;
        printf("ctid %lu 消费结点 %d\n", pthread_self(), tmp->val);
        free(tmp);
        pthread_mutex_unlock(&mtx);
    }
}

int main() {
    pthread_t ptid[5], ctid[5];
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mtx, NULL);

    for (int i = 0; i < 5; i++) {
        pthread_create(ptid + i, NULL, producer, NULL);
        pthread_create(ctid + i, NULL, customer, NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(ptid[i], NULL);
        pthread_join(ctid[i], NULL);
    }
    
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond);
    return 0;

}