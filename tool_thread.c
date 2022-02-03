//
// Created by zhaowei on 2022/1/28.
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;//声明一个锁

void test_function(void *ptr);

int main() {

    int tmp1, tmp2;

    pthread_t thread[2];
    int ret_thrd1, ret_thrd2;

    for (int i = 0; i < 2; ++i) {

        char *message1 = "thread1";

        ret_thrd1 = pthread_create(&thread[i], NULL, (void *) &test_function, (void *) message1);

        if (ret_thrd1 != 0) {
            printf("线程1创建失败\n");
        } else {
            printf("线程1创建成功\n");
        }
    }


    void *retval[2];

    for (int i = 0; i < 2; ++i) {

        tmp1 = pthread_join(thread[i], &retval[i]);
        if (tmp1 != 0) {
            printf("cannot join with thread1\n");
        }
        retval[i] = retval;
        printf("thread1 end\n");
    }

//    for (int j = 0; j < 2; ++j) {
//
//        pthread_exit(retval[j]);
//    }
}

void test_function(void *ptr) {
    pthread_mutex_lock(&mutex);
    sleep(1);
    printf("%s:%d\n", "marss", 1);
    pthread_mutex_unlock(&mutex);
}