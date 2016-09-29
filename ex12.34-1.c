#include <time.h>
#include "csapp.h"
#define MAXTHREADS 32

#define N 3
#define M 20

int matrix_mul();

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
    int i, j, k;
    pthread_t tid[MAXTHREADS];
    int myid[MAXTHREADS];

    for (i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            matrix[i][j] = 0;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            for (k = 0; k < M; k++)
                matrix[i][j] += matrix1[i][k] * matrix2[k][j];

/*
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++)
            printf("%d    ", matrix[i][j]);
        printf("\n");
    }
*/

    return 0;
}












