//main.c
#include <stdio.h>
#include "lib.h"

//extern int sort(int*,int);

int main(){
	int arr[5] = { 793, 25, 468, 6, 94};
	
	printf("Before sort: ");
	for(int i = 0; i < 5; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	sort(arr, 5);
	
	printf("After sort: ");
	for(int i = 0; i < 5; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	return 0;

}
