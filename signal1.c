/* $begin signal1 */
#include "csapp.h"

pid_t Fork(void) 
{
    pid_t pid;

    if ((pid = fork()) < 0)
    unix_error("Fork error");
    return pid;
}

void unix_error(char *msg) /* unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

unsigned int Sleep(unsigned int secs) 
{
    unsigned int rc;

    if ((rc = sleep(secs)) < 0)
    unix_error("Sleep error");
    return rc;
}

void handler1(int sig) 
{
    pid_t pid;

    if ((pid = waitpid(-1, NULL, 0)) < 0)
	unix_error("waitpid error");
    printf("Handler reaped child %d\n", (int)pid);
    Sleep(2);
    return;
}

int main() 
{
    int i, n;
    char buf[MAXBUF];

    if (signal(SIGCHLD, handler1) == SIG_ERR)
	unix_error("signal error");

    /* Parent creates children */
    for (i = 0; i < 3; i++) {
	if (Fork() == 0) { 
	    printf("Hello from child %d\n", (int)getpid());
	    Sleep(1);
	    exit(0);
	}
    }

    /* Parent waits for terminal input and then processes it */
    if ((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0)
	unix_error("read");

    printf("Parent processing input\n");
    while (1)
	; 

    exit(0);
}
/* $end signal1 */
