#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int global = 10;

int main() {
	int local = 10;
	pid_t child_pid;
	child_pid = fork();

	switch(child_pid) {
		case -1:
			printf("fork error\n");	
			break;
		case 0:
			printf("I'm child process\n");
			printf("pid = %d     parent id = %d\n", getpid(), getppid());
			printf("global = %d, local = %d\n", global, local);
			local += 1;
			global += 1;
                        printf("Finally print pid = %d, parent id = %d, global = %d, local = %d\n", getpid(), getppid(), global, local);

			break;
		default:
			printf("I'm parent process\n");
			printf("pid = %d     parent id = %d\n", getpid(), getppid());
			printf("global = %d, local = %d\n", global, local);
			printf("Finally print pid = %d, parent id = %d, global = %d, local = %d\n", getpid(), getppid(), global, local);
			wait(NULL);
			break;
	}
	return 0;
}
