#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
	pid_t pid = fork();
	if(pid < 0) {
		printf("error");
		return 0;
	}
	else if(pid == 0) {
		printf("I am child, pid = %d, ppid = %d\n", getpid(), getppid());
	}
	else {
		printf("I am parent, pid = %d, ppid = %d\n", getpid(), getppid());
		wait(NULL);
	}
	kill(getpid(), SIGKILL);
	return 0;
}
