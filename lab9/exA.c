# include  <fcntl.h>
# include  <mqueue.h>
# include  <stdio.h>
# include  <string.h>
# include  <stdlib.h>
#include <pthread.h>

# define NAME "/myMsgQueue"
# define MAX_MSGSIZE 1000
# define port "ATOB" // ID編號
void *send_t(void * arg);
void *reve_t(void * arg);
void sent(char *str);
int main(){
	pthread_t p1,p2;	
	pthread_create(&p1,NULL,send_t,NULL);
	pthread_create(&p2,NULL,reve_t,NULL);
	//由 receiver 確認是否結束
	pthread_join(p2,NULL);
	return 0;
}
void *send_t(void * arg){
	mqd_t mqd =mq_open(NAME,O_WRONLY|O_CREAT ,0644,NULL);
	if  (mqd ==-1){
		perror("fail to open or create the msg queue.\n");
		return 0;
	}	
	printf("send to receiver:\n");
	int x=1;
	while(x==1){
		char buffer[MAX_MSGSIZE];
		int i;
		for (i=0;i<MAX_MSGSIZE;i++){
			buffer[i]='\0';
		}
		strcat(buffer,port);
		printf("> " );
		char buffer1[MAX_MSGSIZE];
		fgets(buffer1,MAX_MSGSIZE,stdin);
		strcat(buffer,buffer1);


		int send = mq_send(mqd,buffer,strlen(buffer)+1,0);
		if (send ==-1 ){
			perror("fail to send the msg queue.\n");
			return 0;
		}
		if (buffer[0+4]=='e'&&buffer[1+4]=='x'&&buffer[2+4]=='i'&&buffer[3+4]=='t'){
			x=0;
			//當已經對對方發送結束訊號
			//也需要對自身發送訊號
			//(因為程式結束是靠receiver)
			sent("aaaaexit");
		}
	}
	return 0;
}
void sent(char *str){
mqd_t mqd =mq_open(NAME,O_WRONLY|O_CREAT ,0644,NULL);
int send = mq_send(mqd,str,strlen(str)+1,0);
}
void *reve_t(void * arg){
	mqd_t mqd =mq_open(NAME,O_RDONLY|O_CREAT ,0644,NULL);
	if  (mqd ==-1){
		perror("fail to open or create the msg queue.\n");
		return 0;
	}	
	int x=1;
	while(x==1){
		char buffer[MAX_MSGSIZE] ;
		ssize_t msg_size =mq_receive(mqd,buffer,8192,NULL);
		if (msg_size==-1){
			printf("fail to read msg. \n");
			return 0;
		}
		if (strncmp(buffer,port,4)==0){
			// 確認編號非自身
			sent(buffer);
			continue;
		}
		if (buffer[0+4]=='e'&&buffer[1+4]=='x'&&buffer[2+4]=='i'&&buffer[3+4]=='t'){	
			//接收跳出訊號結束程式
			x=0;
			printf("EXIT\n");
			break;
		}
		
		printf("recevied :%s \n",buffer+4);
		
	}
	return 0;
}
