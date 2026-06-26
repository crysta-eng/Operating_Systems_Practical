#include <stdio.h>
#include <pthread.h>

#define THREADS 5

int counter = 0;
pthread_mutex_t mutex;

void *increment(void *arg)
{
    pthread_mutex_lock(&mutex);

    counter++;
    printf("Thread updated counter = %d\n", counter);

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t tid[THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < THREADS; i++)
    {
        pthread_create(&tid[i], NULL, increment, NULL);
    }

    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }

    printf("Final Counter = %d\n", counter);

    pthread_mutex_destroy(&mutex);

    return 0;
}#include <stdio.h>
#include <pthread.h>

#define THREADS 5

int counter = 0;
pthread_mutex_t mutex;

void *increment(void *arg)
{
    pthread_mutex_lock(&mutex);

    counter++;
    printf("Thread updated counter = %d\n", counter);

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t tid[THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < THREADS; i++)
    {
        pthread_create(&tid[i], NULL, increment, NULL);
    }

    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }

    printf("Final Counter = %d\n", counter);

    pthread_mutex_destroy(&mutex);

    return 0;
}
