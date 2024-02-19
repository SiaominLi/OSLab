#include <stdio.h>
#include <pthread.h>

// Declaration of thread condition variables
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;

// mutex which we are going to use avoid race condition.
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// done is a global variable to decides which one of waiting thread should be scheduled
int done = 1;

// Thread function
void *threadFunc(void *n)
{
	while(1) {
			
		// acquire a lock
		pthread_mutex_lock(&lock);
		
		if (done != *((int*)n)) {
			// value of done and n is not equal, hold wait lock on condition variable
			if (*((int*)n) == 1) {
				pthread_cond_wait(&cond1, &lock);
			} 
			else if (*((int*)n) == 3) {
				pthread_cond_wait(&cond2, &lock);
			}
			else {
				pthread_cond_wait(&cond3, &lock);
			}

		}
		// done is equal to n, then print n
		printf("%d ", *((int*)n));

		// Now time to schedule next thread accordingly
		// using pthread_cond_signal()
		if (done == 5) {
			done = 1;
			pthread_cond_signal(&cond1);
		}
		else if(done == 1) {
			done = 3;
			pthread_cond_signal(&cond2);
		} 
		else if (done == 3) {
			done = 5;
			pthread_cond_signal(&cond3);
		}
		
		// Finally release mutex
		pthread_mutex_unlock(&lock);
	}

	return NULL;
}

// Driver code
int main()
{
		pthread_t tid1, tid2, tid3;
		int n1 = 1, n2 = 3, n3 = 5;
		
		// Create 3 threads
		pthread_create(&tid1, NULL, threadFunc, &n1);
		pthread_create(&tid2, NULL, threadFunc, &n2);
		pthread_create(&tid3, NULL, threadFunc, &n3);
		
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		pthread_join(tid3, NULL);
		
		return 0;
}
