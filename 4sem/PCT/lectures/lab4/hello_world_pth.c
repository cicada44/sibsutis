#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

void func(void *s)
{
    pthread_t tid = pthread_self();

    printf("Hello from thread %lu, %s\n", tid, (char *)s);
    sleep(5);
}

int main()
{
    pthread_t tid;

    int rc = pthread_create(&tid, NULL, (void *)(void *)func, "thr");

    if (rc != 0)
    {
        fprintf(stderr, "Can't create new thread\n");
        exit(-1);
    }

    printf("Hello, from main thread %lu\n", pthread_self());

    pthread_join(tid, NULL);
}
