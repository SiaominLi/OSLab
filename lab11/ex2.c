#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void ALRM_handler2() {
	signal(SIGINT, SIG_DFL);
}

void INT_handler2() {
	signal(SIGINT, INT_handler2);
	printf("I am fine!\n");
}

void ALRM_handler1() {
	signal(SIGINT, INT_handler2);
	signal(SIGALRM, ALRM_handler2);
	alarm(3);
}

void INT_handler1() {
	signal(SIGINT, INT_handler1);
	printf("How are you?\n");
}

int main(void) {
	signal(SIGINT, INT_handler1);
	signal(SIGALRM, ALRM_handler1);
	alarm(3);
	
	for(;;) {
		pause();
	}

	return 0;
}
