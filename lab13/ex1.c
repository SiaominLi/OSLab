#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mtx;
static int glob = 0;

static void *threadFunc(void *arg){
	int loops = *((int *)arg);
	int loc, j, s;
	for(j = 0; j<loops; j++){
		s = pthread_mutex_lock(&mtx);
		if(s!=0){
			printf("pthread_mutex_lock ERROR\n");
		}
		
		loc=glob;
		loc++;
		glob=loc;
		
		s = pthread_mutex_unlock(&mtx);
		if(s!=0){
			printf("pthread_mutex_unlock ERROR\n");
		}
	}
	return NULL;
}
int main(int argc, char *argv[]){
	pthread_t t1, t2;
	int loops, s;
	s = pthread_mutex_init(&mtx,NULL);
	loops = atoi(argv[1]);
	
	s = pthread_create(&t1, NULL, threadFunc, &loops);
	if(s!=0){
		printf("pthread_create ERROR\n");
	}
	s = pthread_create(&t2, NULL, threadFunc, &loops);
	if(s!=0){
		printf("pthread_create ERROR\n");
	}
	////////////////////////////////////////
	s = pthread_join(t1, NULL);
	if(s!=0){
		printf("pthread_join ERROR\n");
	}
	s = pthread_join(t2, NULL);
	if(s!=0){
		printf("pthread_join ERROR\n");
	}
	
	printf("glob = %d\n",glob);
	s = pthread_mutex_destroy(&mtx);
	return 0;

}
