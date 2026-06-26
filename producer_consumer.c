#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define THREADS 5

sem_t sem;
int counter = 0;

void *task(void *arg)
{
    sem_wait(&sem);

    counter++;
    printf("Counter = %d\n", counter);

    sem_post(&sem);

    return NULL;
}

int main()
{
    pthread_t threads[THREADS];

    sem_init(&sem, 0, 1);

    for (int i = 0; i < THREADS; i++)
    {
        pthread_create(&threads[i], NULL, task, NULL);
    }

    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&sem);

    return 0;
}
