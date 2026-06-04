#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX 10

int n;
sem_t fork1[MAX];

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    int first = id;
    int second = (id + 1) % n;

    // Last philosopher picks opposite order
    if(id == n - 1)
    {
        first = (id + 1) % n;
        second = id;
    }

    printf("Philosopher %d is Thinking\n", id);

    sem_wait(&fork1[first]);
    sem_wait(&fork1[second]);

    printf("Philosopher %d is Eating\n", id);

    sleep(1);

    sem_post(&fork1[first]);
    sem_post(&fork1[second]);

    printf("Philosopher %d Finished Eating\n", id);

    return NULL;
}

int main()
{
    pthread_t p[MAX];
    int id[MAX];

    printf("Enter number of philosophers: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        sem_init(&fork1[i], 0, 1);

    for(int i = 0; i < n; i++)
    {
        id[i] = i;
        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }

    for(int i = 0; i < n; i++)
        pthread_join(p[i], NULL);

    

    return 0;
}
