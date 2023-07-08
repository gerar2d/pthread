#include<iostream>
#include<pthread.h>
#include<semaphore.h>
#include <string.h>

using namespace std;

void * Writer(void *arg);
void * Reader(void *arg);

sem_t r,w;

int rCount;
char buffer[50];

int main(){
    int x = rand()%2;

    pthread_t rT[3];
    pthread_t wT[2];

    strcpy(buffer,"Not used so far");

    sem_init(&r, 0, 1);
    sem_init(&w, 0, 1);

    for(int i=0; i<3;i++){
        pthread_create(&rT[i], NULL, Reader, (void *)&i);
    }

    for(int i=0; i<2;i++){
        pthread_create(&wT[i], NULL, Writer, (void*)&i);
    }

    switch(x){
        case 0:
            for(int i=0; i<3;i++){
                pthread_join(rT[i], 0);
            }
        break;

        case 1:
            for(int i=0; i<2;i++){
                pthread_join(wT[i], 0);
            }
        break;
        
        default:break;

    }

    sem_destroy (&r);
    sem_destroy (&w);
    return 0;

}

void * Reader(void *arg){
    
    sem_wait(&r);
    rCount++;
    
    if(rCount == 1)
        sem_wait(&w);

    sem_post(&r);
    cout<<"Inside reader Buffer value is \n"<<buffer<<endl;

    sem_wait(&r);
    rCount--;

    if(rCount == 0)
        sem_post(&w);

    sem_post(&r);
}

void * Writer(void *arg){

    int wCount = *(int*)arg;

    sem_wait(&w);
    
    cout<<"writer number"<<wCount<<endl;
    cout<<"Before Inside writer Buffer value is "<<buffer<<endl;
    strcpy(buffer,"test data written to Buffer");
    cout<<"After Inside writer Buffer value is "<<buffer<<endl;

    sem_post(&w);
}