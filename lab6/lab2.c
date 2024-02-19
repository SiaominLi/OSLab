#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
	if(fork() == 0) {
		printf("I'm child process E.\n");
		printf("pid: %d, parentid: %d\n", getpid(), getppid());
		return 0;
	}
	wait(NULL);
	if(fork() == 0) {
		printf("I'm child process D.\n");
		printf("pid: %d, parentid: %d\n", getpid(), getppid());
		return 0;
	}
	wait(NULL);
	if(fork() == 0) {
		if(fork() == 0) {
			printf("I'm child process C.\n");
			printf("pid: %d, parentid: %d\n", getpid(), getppid());
			return 0;
		}
		wait(NULL);
		printf("I'm child process B.\n");
		printf("pid: %d, parentid: %d\n", getpid(), getppid());
		return 0;
	}
	wait(NULL);
	
	printf("I'm parent process A.\n");
	printf("pid: %d, parentid: %d\n", getpid(), getppid());
	return 0;
}
