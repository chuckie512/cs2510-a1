// author: Charles Smith <cas275@pitt.edu>
//
// the stub for the matrix server

#include <pthread.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <stdint.h>
#include "matrix.h"

void *process_connection(void *args){
    int client_fd = *((int *) args);
    
    uint32_t tid = 0;
    int res = 0;

    res = read(client_fd, &tid, sizeof(uint32_t));
    tid = ntohl(tid);
    printf("tid: %d\n", tid);

    int32_t n, m, l;
    res = read(client_fd, &n, sizeof(int32_t));
    n = ntohl(n);

    res = read(client_fd, &m, sizeof(int32_t));
    m = ntohl(m);

    res = read(client_fd, &l, sizeof(int32_t));
    l = ntohl(l);

    printf("%d, %d, %d\n",n,m,l);


    // create the matrix
    int32_t a[n][m];
    int32_t b[m][l];
    int32_t c[n][l];

    int i;
    int j;
    for(i=0; i<n; i++){
        for(j=0; j<m; j++){
            res = read(client_fd, &a[i][j], sizeof(int32_t));
            a[i][j] = ntohl(a[i][j]);
        }
    }
    
    for(i=0; i<m; i++){
        for(j=0; j<l; j++){
            res = read(client_fd, &b[i][j], sizeof(int32_t));
            b[i][j] = ntohl(b[i][j]);
        }
    }

    // actually do the math
    multiply(n,m,l,a,b,c);
    
    printf("mult\n");
    int32_t temp;
    for(i=0; i<n; i++){
        for(j=0; j<l; j++){
            printf("%d ",c[i][j]);
            temp = htonl(c[i][j]);
            write(client_fd, &temp, sizeof(int32_t));
        }
        printf("\n");
    }

    printf("closing\n");
    close(client_fd);
    free(args);
    pthread_exit(NULL);

}

void init_server(char * ip, int port){
    printf("%s:%d\n", ip, port);
}
