#include "csapp.h"

char *tfgets(char *s, int size, FILE *stream);

static void tfget_handler(int sig);


int main(){
    char buf[MAXLINE];

    if (tfgets(buf, MAXLINE, stdin) == NULL)
        printf("BOOM!\n");
    else
        printf("%s", buf);

    exit(0);
}



static sigjmp_buf tfgets_jmp_buf;

// if without a input more than 5s then return NULL
char *tfgets(char *buf, int bufsize, FILE *stream)
{
    pid_t pid, ppid;
    char *bufret;

    ppid = getpid();

    Signal(SIGALRM, tfget_handler);

    if ((pid = Fork()) != 0){
        if (!sigsetjmp(tfgets_jmp_buf, 1)){
            // if the tfgets return then the signal will be discard ?
            bufret = fgets(buf, bufsize, stream);
            Kill(pid, SIGINT);
            return(bufret);
        }
            // if there are no a return in 5s
            return(NULL); 
    }
    else{
        sleep(5);
        Kill(ppid, SIGALRM);
        exit(0);
    }   
}

static void tfget_handler(int sig)
{
    siglongjmp(tfgets_jmp_buf, 1);
}








