#include "stdio.h"
#include "pthread.h"
#include "unistd.h"
#include "stdlib.h"
#include "semaphore.h"
void* inc_thread1(void*);
void* inc_thread2(void*);

sem_t bin_sem;

int main() {
    pthread_t tid1,tid2;
    int ret1 = 0,ret2 = 0;
    void *rec1,*rec2;
    ret1 = sem_init(&bin_sem,0,0);
    if(ret1 != 0) {
        printf("sem initialization failed info : %s\n",strerror(ret1));
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
    sem_destroy(&bin_sem);
    return 0;
}

void* inc_thread1(void *p) {
    unsigned int inc_number1 = 0;
    while(1) {
        printf("inc_thread1 : inc_number1 = %d\n",inc_number1++);
        sem_wait(&bin_sem);
        sleep(1);
    }
    return NULL;
}

void* inc_thread2(void *p) {
    unsigned int inc_number2 = 0;
    while(1) {
        sem_post(&bin_sem);
        printf("inc_thread2 : inc_number2 = %d\n",inc_number2++);
        sleep(2);
    }
    return NULL;
}


