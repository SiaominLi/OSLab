#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#define NAME "/mysharememory"

int main() {
	int shm_fd = shm_open(NAME, O_RDONLY, 0666);
	char *ptr, buffer[1024];

	if(shm_fd == -1) {
		perror("Failed to open or create the shared memory. \n");
		return 1;
	}
	
	char *map_addr = mmap(0, 1024, PROT_READ, MAP_SHARED, shm_fd, 0);
	if(map_addr == MAP_FAILED) {
		perror("Failed to read the map. \n");
		return 1;
	}
	
	printf("Message: %s", map_addr);

	return 0;
}
