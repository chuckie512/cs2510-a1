// author: Charles Smith <cas275@pitt.edu>
// 
// a simple sorting server stub

#include <pthread.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <stdint.h>
#include "matrix.h"

void *process_connection(void *args){
    int client_fd = *((int *) args);

    uint32_t tid = 0;

    read(client_fd, &tid, sizeof(uint32_t));
    tid = ntohl(tid);
    printf("tid: %d\n", tid);

    int32_t n;
    read(client_fd, &n, sizeof(int32_t));
    n = ntohl(n);

    int32_t a[n];

    int i;
    for(i=0; i<n; i++){
        read(client_fd, &a[i], sizeof(int32_t));
        a[i] = ntohl(a[i]);
    }

    sort(n, a);

    int32_t temp;

    for(i=0; i<n; i++){
        temp = htonl(a[i]);
        write(client_fd, &temp, sizeof(int32_t));
    }

    printf("closing\n");
    close(client_fd);
    free(args);
    pthread_exit(NULL);
}

void init_server(char * ip, int port){
    printf("%s:%d\n", ip, port);
    FILE * fp = fopen("./ns.txt","a");
    fprintf(fp, "2 %s:%d\n", ip, port);
    fclose(fp);
}

