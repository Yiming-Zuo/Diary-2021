#include <stdio.h>
#include <pthread.h>
#include <string.h>

struct Student {
    int age;
    char name[24];
};

void *callBack(void *arg) {
    printf("pthread: %d\n", pthread_self());
    static struct Student st;
    st.age = 20;
    strcpy(st.name, "lee");
    pthread_exit(&st);  // void *
    printf("num = %d\n", *(int *)arg);
}

int main() {
    pthread_t tid;
    int num = 100;
    int ret = pthread_create(&tid, NULL, callBack, (void *)&num);
    if (ret != 0) {
        printf("pthread_creat: %s\n", strerror(ret));
    }
    printf("main tip: %d\n", pthread_self());
    // pthread_exit(0);  // 主线程退出，不会对子线程造成影响
    struct Student *st;
    pthread_join(tid, (void **)&st);  // 回收子线程资源 void **
    printf("pthread return: name=%s, age=%d\n", st->name, st->age);
    return 0;
}