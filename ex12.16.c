#include "csapp.h"
#define MAXTHREADS 128

void *thread(void *vargp);

int main(int argc, char **argv){
    pthread_t tid[MAXTHREADS];
    int i, n, myid[MAXTHREADS];
    if (argc != 2){
        printf("usage: %s <threads>\n", argv[0]);
        exit(0);
    }

    n = atoi(argv[1]);

    if (n > MAXTHREADS){
        printf("too many threads!\n");
        exit(0);
    }

    for(i = 0; i < n; i++){
        myid[i] = i;
        Pthread_create(&tid[i], NULL, thread, NULL);
    }

    for(i = 0; i < n; i++){
        Pthread_join(tid[i], NULL);
    }

    exit(0);
}

void *thread(void *vargp)   /* Thread routine */{
    printf("Hello, world!\n");
    return NULL;
}






