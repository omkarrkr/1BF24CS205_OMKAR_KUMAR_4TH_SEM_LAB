#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;
int p_count, c_count;

sem_t mutex, empty, full;

void *producer(void *arg)
{
    for(int i = 0; i < p_count; i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = i;
        printf("Produced %d\n", i);

        in = (in + 1) % SIZE;

        sem_post(&mutex);
        sem_post(&full);
    }

    return NULL;
}

void *consumer(void *arg)
{
    for(int i = 0; i < c_count; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        printf("Consumed %d\n", buffer[out]);

        out = (out + 1) % SIZE;

        sem_post(&mutex);
        sem_post(&empty);
    }

    return NULL;
}

int main()
{
    pthread_t p, c;

    printf("Enter items to produce: ");
    scanf("%d", &p_count);

    printf("Enter items to consume: ");
    scanf("%d", &c_count);

    if(c_count > p_count)
    {
        printf("Consumption cannot be greater than production\n");
        return 0;
    }

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    return 0;
}
