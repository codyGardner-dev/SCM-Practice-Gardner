#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define PRO_NO 2
#define CON_NO 2

int n = 0;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty, full, mutex;

pthread_t tid;
pthread_t producerThreads[100], consumerThreads[100];

int pros = -1;
int cons = -1;

void *producer(void* param){
	sem_wait(&empty);
	pros++;
	sem_wait(&mutex);
	buffer[in] = n;
	printf("Producer %d produced item %d \n", pros, buffer[in]);
	in = (in+1)%BUFFER_SIZE;
	n++;
	sem_post(&mutex);
	pros--;
	sem_post(&full);
	return NULL;
}

void *consumer(void* param){
	sem_wait(&full);
	cons++;
	sem_wait(&mutex);
	if(in > 0){
	printf("Consumer %d consumed item %d \n", cons, buffer[out]);
	buffer[out] = 0;
	}
	sem_post(&mutex);
	out = (out+1)%BUFFER_SIZE;
	cons--;
	sem_post(&empty);
	return NULL;
}
