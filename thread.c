#include "stdio.h"
#include "pthread.h"
#include "unistd.h"
#include "stdlib.h"
void* inc_thread1(void*);
void* inc_thread2(void*);

pthread_mutex_t work_mutex;
pthread_cond_t cond;

int main() {
    pthread_t tid1,tid2;
    int ret1 = 0,ret2 = 0;
    void *rec1,*rec2;
    ret1 = pthread_mutex_init(&work_mutex,NULL);
    if(ret1 != 0) {
        printf("Mutex initialization failed info : %s\n",strerror(ret1));
        exit(EXIT_FAILURE);
    }
    ret1 = pthread_cond_init(&cond,NULL);
    if(ret1 != 0) {
        printf("Cond initialization failed info : %s\n",strerror(ret1));
        exit(EXIT_FAILURE);
    }
    ret1 = pthread_create(&tid1,NULL,inc_thread1,NULL);
    if(ret1 != 0) {
        printf("inc_thread1 create failed info : %s\n",strerror(ret1));
        exit(EXIT_FAILURE);
    }
    sleep(1);

    ret2 = pthread_create(&tid2,NULL,inc_thread2,NULL);
    if(ret2 != 0) {
        printf("inc_thread2 create failed info : %s\n",strerror(ret2));
        exit(EXIT_FAILURE);
    }

    ret1 = pthread_join(tid1,&rec1);
    if(ret1 != 0) {
        printf("pthread_join failed info : %s\n",strerror(ret1));
        exit(EXIT_FAILURE);
    }
    ret2 = pthread_join(tid2,&rec2);
    if(ret2 != 0) {
        printf("pthread_join failed info : %s\n",strerror(ret2));
        exit(EXIT_FAILURE);
    }
    pthread_mutex_destroy(&work_mutex);
    pthread_cond_destroy(&cond);
    return 0;
}

void* inc_thread1(void *p) {
    unsigned int inc_number1 = 0;
    while(1) {
        pthread_mutex_lock(&work_mutex);
        printf("inc_thread1 : inc_number1 = %d\n",inc_number1++);
        pthread_cond_wait(&cond,&work_mutex);
        pthread_mutex_unlock(&work_mutex);
        sleep(1);
    }
    return NULL;
}

void* inc_thread2(void *p) {
    unsigned int inc_number2 = 0;
    while(1) {
        pthread_mutex_lock(&work_mutex);
        pthread_cond_signal(&cond);
        printf("inc_thread2 : inc_number2 = %d\n",inc_number2++);
        pthread_mutex_unlock(&work_mutex);
        sleep(2);
    }
    return NULL;
}


