#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
	int freeframe[16] = {0};
	char logic_memA[3][2] = {{'a', 'b'}, {'e', 'f'}, {'c', 'd'}};
	char logic_memB[3][2] = {{'r', 'x'}, {'y', 'y'}, {'z', 'z'}};
	int pagetA[3] = {-1,-1,-1};
	int pagetB[3] = {-1,-1,-1};
	
	//Generate random page table A and set freeframe to 1
	for(int i = 0; i < 3; i++) {
		srand(time(NULL));
		while(1) {
			int ta = rand()%16;
			int tb = rand()%16;
			if(freeframe[ta] == 0 && freeframe[tb] == 0 && ta != tb) {
				pagetA[i] = ta;
				freeframe[ta] = 1;
				pagetB[i] = tb;
				freeframe[tb] = 1;
				break;
			}
		}
	}
	printf("processA's logical memory\n");
	printf("page\tdata\n");
	for(int i = 0; i < 3; i++) {
		printf("%d\t%c%c\n", i, logic_memA[i][0], logic_memA[i][1]);
	}
	
	printf("processA's page table\n");
	for(int i = 0; i < 3; i++) {
		printf("%d\t%d\n", i, pagetA[i]);
	}
	
	printf("processB's logical memory\n");
	printf("page\tdata\n");
	for(int i = 0; i < 3; i++) {
		printf("%d\t%c%c\n", i, logic_memB[i][0], logic_memB[i][1]);
	}
	
	printf("processB's page table\n");
	for(int i = 0; i < 3; i++) {
		printf("%d\t%d\n", i, pagetB[i]);
	}
	
	printf("physical memory:\n");
	printf("frame\toffset\tdata\n");
	for(int i = 0; i < 16; i++) {
		int whichmem = -1;
		int floor = -1;
		for(int j = 0; j < 3; j++) {
			if(i == pagetA[j]) {
				whichmem = 1;
				floor = j;
				break;
			}
			if(i == pagetB[j]) {
				whichmem = 2;
				floor = j;
				break;
			}
		}
		if(whichmem == 1) {
			printf("%d\t0\t%c\n", i, logic_memA[floor][0]);
			printf("%d\t1\t%c\n", i, logic_memA[floor][1]);
		}
		else if(whichmem == 2) {
			printf("%d\t0\t%c\n", i, logic_memB[floor][0]);
			printf("%d\t1\t%c\n", i, logic_memB[floor][1]);
		}
		else {
			printf("%d\t0\t\n", i);
			printf("%d\t1\t\n", i);
		}
	}
	
	int freelist[16] = {0};
	int flag = 6;
	printf("free-frame table:\n");
	
	int t;
	for(int i = 0; i < 10 ; i++)  {
		t = rand()%16;
		//printf("%d\n",i);
		if(freeframe[t] == 0) {
			//flag++;
			freeframe[t] = 1;
			printf("%d ", t);			
		}
		else i--;
	}
	printf("\n");
	
	return 0;
}
