#include "csapp.h"

typedef struct {                    /* Represents a pool of connected descriptors */
    int maxfd;                      /* Largest descriptor in read_set */
    fd_set read_set;                /* Set of all active descriptors */
    fd_set ready_set;               /* Subset of descriptors ready for reading */
    int nready;                     /* Number of ready descriptors from select */
    int maxi;                       /* Highwater index into client array */
    int clientfd[FD_SETSIZE];       /* Set of active descriptors */
    rio_t clientrio[FD_SETSIZE];    /* Set of active read buffers */
} pool;


int byte_cnt = 0;                   /* Counts total bytes received by server */
int main(int argc, char **argv){
    int listenfd, connfd, port;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    static pool pool;
    
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    port = atoi(argv[1]);
    listenfd = Open_listenfd(port);
    init_pool(listenfd, &pool);
    
    while (1) {
        /* Wait for listening/connected descriptor(s) to become ready */
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd+1, &pool.ready_set, NULL, NULL, NULL);
        
        /* If listening descriptor ready, add new client to pool */
        if (FD_ISSET(listenfd, &pool.ready_set)) {
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            add_client(connfd, &pool);
        }

        /* Echo a text line from each ready connected descriptor */
        check_clients(&pool);
    }
}




void check_clients(pool *p)
{
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;
    

    for (i = 0; (i <= p->maxi) && (p->nready > 0); i++) {
        connfd = p->clientfd[i];
        rio = p->clientrio[i];
        
        /* If the descriptor is ready, echo a text line from it */
        if ((connfd > 0) && (FD_ISSET(connfd, &p->ready_set))) {
            p->nready--;

            if ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
                byte_cnt += n;
                printf("Server received %d (%d total) bytes on fd %d\n",
                    n, byte_cnt, connfd);
                Rio_writen(connfd, buf, n);
            }




            /* answer */
            else if (n = -1){
                printf("Server encounted read error!\n");
            }




            /* EOF detected, remove descriptor from pool */
            else {
                Close(connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[i] = -1;
            }
        }
    }
}





