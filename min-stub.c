// author: Charles Smith <cas275@pitt.edu>
// 
// a min server stub

#include <pthread.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <stdint.h>
#include "matrix.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "register.c"

#define CACHE_SIZE 5

static uint32_t cache[CACHE_SIZE][2];
static uint32_t cache_pt = 0;

void *process_connection(void *args){
    int client_fd = *((int *) args);

    uint32_t tid = 0;
    int i;
    read(client_fd, &tid, sizeof(uint32_t));
    tid = ntohl(tid);
    printf("tid: %d\n", tid);
    
    for(i=0; i<CACHE_SIZE; i++){
        if(cache[i][0] == tid){
            printf("found tid in cache, value= %d\n", cache[i][1]);
            int32_t cached_res = cache[i][1];
            cached_res = htonl(cached_res);
            write(client_fd, &cached_res, sizeof(int32_t));
            close(client_fd);
            free(args);
            pthread_exit(NULL);
            return;
        }
    }

    int32_t n;
    read(client_fd, &n, sizeof(int32_t));
    n = ntohl(n);

    int32_t a[n];

    
    for(i=0; i<n; i++){
        read(client_fd, &a[i], sizeof(int32_t));
        a[i] = ntohl(a[i]);
    }


    int32_t temp = min(n, a);

    cache_pt = (cache_pt +1) % CACHE_SIZE;
    cache[cache_pt][1] = temp;
    cache[cache_pt][0] = tid;

    temp = htonl(temp);
    write(client_fd, &temp, sizeof(int32_t));


    
    printf("closing\n");
    close(client_fd);
    free(args);
    pthread_exit(NULL);
}

void init_server(char * ip, int port){
    printf("%s:%d\n", ip, port);
    //    FILE * fp = fopen("./ns.txt", "a");
    //    fprintf(fp, "3 %s:%d\n", ip, port);
    //    fclose(fp);
    
    register_fun(3, ip, port);
}
