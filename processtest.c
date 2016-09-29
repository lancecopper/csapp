#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int i = 0,j = 0;
	int pid;
	if ((pid = fork()) == 0){
		i++;
		j++;
		printf("i=%d, j=%d\n", i,j);
		exit(0);
	}
	wait(NULL);
	i++;
	j++;
	printf("i=%d, j=%d\n", i,j);
	return 0;
}




