#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

sem_t *mutex;
int count = 0;

void inc(void);
void dec(void);

int main(void) {
	mutex = sem_open("/mysem" , O_CREAT , 0644 , 1);
	//0644
	int i = 0;
	pthread_t id[4];
	pthread_create(&id[0], NULL, (void*)dec, NULL);
	pthread_create(&id[1], NULL, (void*)inc, NULL);
	pthread_create(&id[2], NULL, (void*)dec, NULL);
	pthread_create(&id[3], NULL, (void*)inc, NULL);
	for(i=0; i<4; i++) {
		pthread_join(id[i], NULL);
	}
	sem_close(mutex);
	printf("output is %d\n", count);
	sem_unlink("/mysem");
	pthread_exit(NULL);
}

void inc(void) {
	sem_wait(mutex);
	int i = 0;
	for(i=0; i<5; i++) {
		count++;
		printf("count = %d\n", count);
	}
	sem_post(mutex);
	pthread_exit(NULL);
}

void dec(void) {
	sem_wait(mutex);
	int i = 0;
	for(i=0; i<5; i++) {
		count--;
		printf("count = %d\n", count);
	}
	sem_post(mutex);
	pthread_exit(NULL);
}
