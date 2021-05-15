#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define MICROSECS(t) (1000000 * (t).tv_sec + (t).tv_usec)
#include <pthread.h>

int array [1000];

void *loop(void *threadarg){
    int increment_idx = *((int*) threadarg);
    int i;
    for (i = 0; i < 1000*1000*100;i++){
    array[increment_idx] ++;
    }
}


int main(){
    struct timeval t0, t1;
    pthread_t thread1, thread2;
    unsigned long duration;
    int idx1 = 0;
    int idx2 = 1;
    int idx3 = 8;
    int idx4 = 16;
    gettimeofday(&t0, NULL);
    loop((void*) &idx1);
    loop((void*) &idx2);
    gettimeofday(&t1, NULL);
    duration = MICROSECS(t1) - MICROSECS(t0);
    printf("time sequential: %luμs\n", duration);
    gettimeofday(&t0, NULL);
    pthread_create(&thread1, NULL, loop, (void*)&idx1);
    pthread_create(&thread2, NULL, loop, (void*)&idx2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    gettimeofday(&t1, NULL);
    duration = MICROSECS(t1) - MICROSECS(t0);
    printf("time parallel direct neighbour: %luμs\n", duration);
    gettimeofday(&t0, NULL);
    pthread_create(&thread1, NULL, loop, (void*)&idx1);
    pthread_create(&thread2, NULL, loop, (void*)&idx3);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    gettimeofday(&t1, NULL);
    duration = MICROSECS(t1) - MICROSECS(t0);
    printf("time parallel with stride of 8: %luμs\n", duration);
    gettimeofday(&t0, NULL);
    pthread_create(&thread1, NULL, loop, (void*)&idx1);
    pthread_create(&thread2, NULL, loop, (void*)&idx4);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    gettimeofday(&t1, NULL);
    duration = MICROSECS(t1) - MICROSECS(t0);
    printf("time parallel with stride of 16: %luμs\n", duration);


}