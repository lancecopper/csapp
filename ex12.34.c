#include <time.h>
#include "csapp.h"
#define MAXTHREADS 32

#define N 3
#define M 20

int matrix_mul();
void *mult(void *vargp);

int matrix1[N][M];
int matrix2[M][N];
int matrix[N][N];



int main(int argc, char **argv){
    clock_t start, end;
    start = clock();
    int i, j;

    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            matrix1[i][j] = 9;

    for (i = 0; i < M; i++)
        for (j = 0; j < N; j++)
            matrix2[i][j] = 9;

    

    /* code to time */
    for (i=0; i<1000; i++)
        matrix_mul();

    end = clock();
    printf("start=%ld, end=%ld\n", start, end);
    printf("time=%f\n", ((double)(end - start)));
}


int matrix_mul(){
    long i, j;
    pthread_t tid[MAXTHREADS];
    int myid[MAXTHREADS];

    for (i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            matrix[i][j] = 0;

    for (i = 0; i < N; i++){
        myid[i] = i;
        pthread_create(&tid[i], NULL, mult, &myid[i]);
    }

    for (i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

/*
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++)
            printf("%d    ", matrix[i][j]);
        printf("\n");
    }
*/
    return 0;
}

void *mult(void *vargp){
    int myid = *((int*)vargp);
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            matrix[myid][i] += matrix1[myid][j] * matrix2[j][i];

    return NULL;

}












