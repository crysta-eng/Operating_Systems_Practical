#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int in = 0;
int out = 0;
int item = 0;

sem_t mutex;
sem_t empty;
sem_t full;

void *producer(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = ++item;
        printf("Produced %d\n", item);

        in = (in + 1) % SIZE;

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }

    return NULL;
}

void *consumer(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        printf("Consumed %d\n", buffer[out]);

        out = (out + 1) % SIZE;

        sem_post(&mutex);
        sem_post(&empty);

        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_t producerThread;
    pthread_t consumerThread;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
