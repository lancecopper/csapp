#include "csapp.h"



#define N 2



void unix_error(char *msg) /* unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

pid_t Fork(void) 
{
    pid_t pid;

    if ((pid = fork()) < 0)
	unix_error("Fork error");
    return pid;
}



int main(){
	int status, i;
	pid_t pid;

	for (i = 0; i < N; i++)
		if((pid = Fork()) == 0)
			exit(100+i);

	while ((pid = waitpid(-1, &status, 0)) > 0) {
		if (WIFEXITED(status))
			printf("child %d terminated normally with exit status=%d\n",
				   pid, WEXITSTATUS(status));
		else
			printf("child %d terminated abnormally\n", pid);
	}
	if (errno != ECHILD)
		unix_error("waitpid error");
	exit(0);

}





