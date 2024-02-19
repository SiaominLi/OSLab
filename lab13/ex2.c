#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int avail = 0;

static void *producer(void *arg){
	int cnt = atoi((char *) arg);
	int s, j;
	
	for(j=0; j<cnt; j++){
		sleep(1);
		s = pthread_mutex_lock(&mtx);
		avail++;
		s = pthread_mutex_unlock(&mtx);
		s = pthread_cond_signal(&cond);
	}
	return NULL;
}
		

int main(int argc, char *argv[]){
	pthread_t tid;
	int s, j;
	int totRequired;
	int numConsumed;
	
	bool done;
	time_t t;
	t = time(NULL);
	
	///////create all threads////////
	totRequired = 0;
	for(j=1; j<argc; j++){
		totRequired += atoi(argv[j]);
		s = pthread_create(&tid , NULL , producer , argv[j]);
		if(s!=0){
			printf("pthread_create ERROR\n");
		}
	}
	
	numConsumed = 0;
	done = false;
	
	for(int c=0;c<5;c++){
		pthread_mutex_lock(&mtx);
		
		if(avail == 0){
			s = pthread_cond_wait(&cond, &mtx);
			printf("wait avail = 0\n");
		}
		while(avail > 0){
			numConsumed++;
			avail--;
			printf("T=%ld: numConsumed=%d\n",(long)(time(NULL)-t),numConsumed);
			done = numConsumed >= totRequired;
		}
		
		pthread_mutex_unlock(&mtx);
		
		if(done) break;
	}
	s = pthread_mutex_destroy(&mtx);
	return 0;
}
		
		
		
		
		
		
		
