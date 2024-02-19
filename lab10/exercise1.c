#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

static __thread int glob = 0;

static void *incr(int* loops){
	int loc, j, t;
	for (j = 0; j < *loops; j++){
		loc = glob;
		loc++;
		glob = loc;
	}
	t = (*loops==50)?1:2;
	printf("thread%d, glob = %d\n", t, glob);
}

int main(){
	printf("(main thread) glob value before run 2 threads = %d\n", glob);

	int t1 = 50, t2 = 100;
	pthread_t id[2];
	pthread_create(&id[0], NULL, incr, &t1);
	pthread_create(&id[1], NULL, incr, &t2);
	
	pthread_join(id[0], NULL);
	pthread_join(id[1], NULL);
	
	printf("(main thread) glob value after run 2 threads = %d\n", glob);
	return 0;
}

