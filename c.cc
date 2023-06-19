#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctime>
#include <unistd.h>

#define MAX_T 2

pthread_mutex_t mutexBuffer;

void *producer(void *args);
void *consumer(void *args);

int count = 0;
int countLimit = 0;
int bufferSize;
int *buffer;
int in = 0;
int out = 0;


int main(int argc, char* argv[]) 
{
    srand(time(0));
    pthread_t t[MAX_T];
    int i;
    
    printf ("buffer size: ");
    scanf ("%d",&bufferSize);

    buffer = (int *) malloc(bufferSize * sizeof(int));
    
    printf ("count limit: ");
    scanf ("%d",&countLimit);
    
    for (i = 0; i < MAX_T; i++)
    {
        if (i % 2 == 0)
        {
            if (pthread_create(&t[i], NULL, &producer, NULL) != 0)
            {
                perror("failed to create thread");
            }
        }
        else
        {
            if (pthread_create(&t[i], NULL, &consumer, NULL) != 0)
            {
                perror("failed to dreate thread");
            }
        }
    }
    for (i =0; i < MAX_T; i++)
    {
        if (pthread_join(t[i], NULL) != 0)
        {
            perror("Failed to join thread");
        }
    }
    pthread_mutex_destroy(&mutexBuffer);
    return 0;
}

void *producer(void *args)
{
    while(count < countLimit && count < bufferSize)
    {
        while (((in + 1) % bufferSize) == out);        
        int x = rand() % 100;
        pthread_mutex_lock(&mutexBuffer);
        buffer[in] = x;
        printf("producer: %d\n",x);
        in = (in + 1) % bufferSize;
        count++;
        pthread_mutex_unlock(&mutexBuffer);
        sleep(1);       
    }
}

void *consumer(void *args)
{
    while(count < countLimit && count < bufferSize)
    {
        while (in == out);
        pthread_mutex_lock(&mutexBuffer);   
        int y = buffer[out];
        buffer[in] = y;
        printf("consumer: %d\n", buffer[out]);
        out = (out + 1) % bufferSize;
        count++;
        pthread_mutex_unlock(&mutexBuffer);

    }
    if (countLimit > bufferSize)
    {
        printf("Buffer is full\n");
    }
}