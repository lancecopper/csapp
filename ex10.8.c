#include "csapp.h"

int main(int argc, char **argv){
	struct stat stat;
	char *type, *readok;

	fstat(atoi(argv[1]), $stat);

	if (S_ISREG(stat.st_mode))
		type = "regular";
	else if (S_ISREG(stat.st_mode))
		type = "directory";
	if ((stat.st_mode & S_IRUSR))
		readok = "yes";
	else 
		readok = "no";
	printf("type: %s, read: %s\n", type, readok);
	exit(0);
}



