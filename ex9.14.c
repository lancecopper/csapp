#include "csapp.h"

int main(){
	struct stat stat;
	char *start;
	int fd;

	fd = Open("./hello.txt", O_RDWR, 0);

	start = Mmap(NULL, 1, PROT_WRITE, MAP_SHARED, fd, 0);

	close(fd);

	if (start == MAP_FAILED)
		return -1;

	(*start) = 'J';

	munmap(start, 1);

	sleep(10);

	return 0;
}







