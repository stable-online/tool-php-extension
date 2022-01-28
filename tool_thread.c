//
// Created by zhaowei on 2022/1/28.
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void test_function (void *ptr);

void run(long number){

    int tmp1, tmp2;
    void *retval;
    pthread_t thread1, thread2;
    char *message1 = "thread1";
    char *message2 = "thread2";

    int ret_thrd1, ret_thrd2;

    ret_thrd1 = pthread_create(&thread1, NULL, (void *) &test_function, (void *) message1);
    ret_thrd2 = pthread_create(&thread2, NULL, (void *) &test_function, (void *) message2);

    if (ret_thrd1 != 0) {
        printf("线程1创建失败\n");
    } else {
        printf("线程1创建成功\n");
    }

    if (ret_thrd2 != 0) {
        printf("线程2创建失败\n");
    } else {
        printf("线程2创建成功\n");
    }

    //同样，pthread_join的返回值成功为0
    tmp1 = pthread_join(thread1, &retval);
//    printf("thread1 return value(retval) is %d\n", (int)retval);
//    printf("thread1 return value(tmp) is %d\n", tmp1);
    if (tmp1 != 0) {
        printf("cannot join with thread1\n");
    }
    printf("thread1 end\n");

    tmp2 = pthread_join(thread2, &retval);
//    printf("thread2 return value(retval) is %d\n", (int)retval);
    printf("thread2 return value(tmp) is %d\n", tmp1);
    if (tmp2 != 0) {
        printf("cannot join with thread2\n");
    }
    printf("thread2 end\n");
}

void test_function(void *ptr ) {
    int i = 0;
    for (int i; i<5; i++) {
        printf("%s:%d\n", (char *)ptr, i);
    }
}