#include <stdio.h>
#include <time.h>
#define HAVE_STRUCT_TIMESPEC
#pragma warning(disable : 4996) 
#include <pthread.h>
#include <semaphore.h>
#include <windows.h>
#define SIZE 10
sem_t empty, full, mutex;
int *buffer;
int pptr = 0, cptr = 0;
void * producer() {
	while (1) {
		sem_wait(&empty);
		printf("Producer producing item%d in Buffer\n", pptr);
		sem_wait(&mutex);
		*(buffer + pptr) = pptr;
		pptr++;
		Sleep(2000);
		sem_post(&full);
		sem_post(&mutex);

	}
	return NULL;
}
void * consumer() {
	int i;
	while (1) {
		sem_wait(&mutex);
		i = *(buffer + cptr);
		cptr++;
		sem_post(&mutex);
		sem_wait(&full);
		printf("consumer Consuming item%d\n", i);
		Sleep(5000);
		sem_post(&empty);
	}
	return NULL;
}
int main() {
	setbuf(stdout, NULL);
	int z = 0;
	buffer = &z;
	pthread_t con, pro;
	sem_init(&empty, 0, SIZE);
	sem_init(&full, 0, 0);
	sem_init(&mutex, 0, 1);
	pthread_create(&pro, NULL, producer, NULL);
	pthread_create(&con, NULL, consumer, NULL);
	pthread_join(pro, NULL);
	pthread_join(con, NULL);
	return 0;
}

