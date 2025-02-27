#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

pthread_mutex_t mutex;

long timeval_diff(struct timeval *start, struct timeval *end)
{
    return ((end->tv_sec - start->tv_sec) * 1000000L + (end->tv_usec - start->tv_usec));
}

void* increment_counter(void* counter)
{
    int *c;
    int i;

    i = 0;
    c = (int *)counter;
    while (i < 100)
    {
        pthread_mutex_lock(&mutex);
        (*c)++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
    return (NULL);
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;
    int counter;
    struct timeval  start;
    struct timeval  end;

    counter = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thread1, NULL, increment_counter, (void *)&counter);
    pthread_create(&thread2, NULL, increment_counter, (void *)&counter);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&mutex);
    printf("Final counter value: %d\n", counter);
    gettimeofday(&start, NULL);
    usleep(2000000);
    gettimeofday(&end, NULL);
    printf("%ld\n", timeval_diff(&start, &end) / 1000000L);
}
