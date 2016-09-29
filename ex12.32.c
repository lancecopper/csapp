#include "csapp.h"

char *tfgets_select(char *buf, int bufsize, FILE *stream);

int main(){
    char buf[MAXLINE];

    if (tfgets_select(buf, MAXLINE, stdin) == NULL)
        printf("BOOM!\n");
    else
        printf("%s", buf);

    exit(0);
}


char *tfgets_select(char *buf, int bufsize, FILE *stream){
	fd_set read_set;	
	struct timeval sleep = {5, 0};

	int fd = fileno(stream);
	FD_ZERO(&read_set);
	FD_SET(fd, &read_set);

	Select(fd+1, &read_set, NULL, NULL, &sleep);
	if (FD_ISSET(fd, &read_set))
		return fgets(buf, bufsize, stream);
	else
		return NULL;
}




