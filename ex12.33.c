#include "csapp.h"

#define TIMEOUT 5


char *tfgets_thread(char *s, int size, FILE *stream);
void *fgets_thread(void *vargp);
void *sleep_thread(void *vargp);

typedef struct {
    char * s;
    int size;
    FILE *stream;
} args_t;

char *retval;


int main(){
    char buf[MAXLINE];

    if (tfgets_thread(buf, MAXLINE, stdin) == NULL)
        printf("BOOM!\n");
    else
        printf("%s", buf);

    exit(0);
}


void *sleep_thread(void *vargp){
    pthread_t fget_tid = *((pthread_t *)vargp);
    pthread_detach(pthread_self());
    sleep(TIMEOUT);
    pthread_cancel(fget_tid);
    return NULL;
}

void *fgets_thread(void *vargp){
    //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    args_t *argument = (args_t*)vargp;
    retval = fgets(argument->s, argument->size, argument->stream);
    return NULL;
}

char *tfgets_thread(char *s, int size, FILE *stream) {
    retval = NULL;
    args_t argument = {s, size, stream};
    pthread_t fget_tid, sleep_tid;

    pthread_create(&fget_tid, NULL, fgets_thread, &argument);
    pthread_create(&sleep_tid, NULL, sleep_thread, &fget_tid);
    pthread_join(fget_tid, NULL);
    return retval;
}


