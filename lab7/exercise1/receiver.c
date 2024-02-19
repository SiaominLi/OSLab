#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <mqueue.h>
#define NAME "/msgq1"
#define MAX_SIZE 1000

int main(int argc, char **argv) {
	mqd_t mq1;
	char buffer[MAX_SIZE+1];
	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = MAX_SIZE+1;
	attr.mq_curmsgs = 0;

	mq1 = mq_open(NAME, O_RDONLY|O_CREAT, 0644, &attr);
	if(mq1 == -1) {
		perror("Failed to open or create the msg\n");
		return 1;
	}
	
	while(1) {
		ssize_t bytes_read = mq_receive(mq1, buffer, 8192, NULL);
		if(bytes_read < 0) {
			perror("Failed to read the msg");
			return 1;
		}
		buffer[bytes_read] = '\0';
		if(strncmp(buffer, "exit", 4) == 0) {
			break;
		}
		printf("received: %s", buffer);
	}

	int s_close = mq_close(mq1);
	if(s_close == -1) {
		perror("Failed to close the msg\n");
		return 1;
	}

	int unlink = mq_unlink(NAME);
	if(unlink == -1) {
		printf("Failed to unlink the msg\n");
		return 1;
	}
	printf("Exiting receive...\n");

	return 0;
}
