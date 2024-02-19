#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *PrintHello(void *arg)
{
	printf("This is Hello Thread\n");
	printf("Thread ID:%lu\n",pthread_self());
	printf("Argument:%d\n",*(int*)arg);
	int re = 50;
	pthread_exit((void*)re);
}

int main()
{
	pthread_t thread;
	int rc, t = 100;
	void *ret;
	rc = pthread_create(&thread, NULL, PrintHello, &t);
	if(rc) {
		printf("CREATE ERROR\n");
		exit(-1);
	}
	rc = pthread_join(thread, &ret);
	if(rc) {
		printf("JOIN ERROR\n");
		exit(-1);
	}
	printf("return value:%d\n",(int)ret);
	return 0;
}
