#include "csapp.h"

int main(int argc, char **argv){
	struct in_addr inaddr;
	unsigned int addr;

	if (argc != 2){
		fprintf(stderr, "usage: %s <dotted-decimal>\n", argv[0]);
		exit(0);
	}

	if (inet_aton(argv[1], &inaddr) == 0)
		app_error("inet_aton error");

	addr = ntohl(inaddr.s_addr);
	printf("0x%x\n", addr);

	exit(0);
}





