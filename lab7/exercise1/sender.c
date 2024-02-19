#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <mqueue.h>

#define NAME "/msgq1"
#define MAX_SIZE 1000

int main() {
	mqd_t mq1;
	char buffer[MAX_SIZE];
	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = MAX_SIZE;
	attr.mq_curmsgs = 0;

	mq1 = mq_open(NAME, O_WRONLY|O_CREAT, 0644, &attr);
	if(mq1 == -1) {
		perror("Failed to open or create the message queue. \n");
		return 1;
	}
	while(1) {
		printf("send to receiver:\n");
		for(int i = 0; i < sizeof(buffer); i++) {
			buffer[i] = '\0';
		}
		printf("> ");
		fgets(buffer, MAX_SIZE, stdin);
		
		int send = mq_send(mq1, buffer, strlen(buffer)+1, 0);
		if(send == -1) {
			perror("Failed to send a message\n");
			return 1;
		}
		if(strncmp(buffer, "exit" , 4) == 0) {
			break;
		}
	}

	return 0;
}
