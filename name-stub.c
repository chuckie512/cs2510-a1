// author: Charles Smith <cas275@pitt.edu>
//
// a name-server implimintaiton


#include <pthread.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <stdint.h>

static char * ips[5][50];

void *process_connection(void *args){
    int client_fd = *((int *) args);

    uint32_t tid = 0;
    read(client_fd, &tid, sizeof(uint32_t));
    tid = ntohl(tid);
    printf("tid: %d\n", tid);

    int32_t request = 0;
    read(client_fd, &request, sizeof(int32_t));

    if(request == 0){ // register
        int32_t function_number = 0;
        read(client_fd, &function_number, sizeof(int32_t));
        function_number = ntohl(function_number);
        if(function_number > 4){ // invalid
            printf("invalid\n");
            close(client_fd);
            free(args);
            pthread_exit(NULL);
        }
        if(function_number <= 0){ // alive check
            int32_t yes = 1;
            yes = htonl(yes);
            write(client_fd, &yes, sizeof(int32_t));
            close(client_fd);
            free(args);
            pthread_exit(NULL);
        }
        // else
        int32_t length = 0;

        read(client_fd, &length, sizeof(int32_t));
        length = ntohl(length);

        read(client_fd, &ips[function_number], sizeof(char)*length);
        printf("registed %d, %s\n", function_number, ips[function_number]);
    }
    else{ //request
        printf("request\n");
        int32_t function_number = 0;
        read(client_fd, &function_number, sizeof(int32_t));
        function_number = ntohl(function_number);
        printf("function %d\n", function_number);
        
        char temp[256];
        bzero(temp,256);
        strncpy(temp, ips[function_number], 255);

        int32_t length = strlen(temp);
        printf("%d, %s\n", length, temp);
        
        int32_t tlength = htonl(length);
        write(client_fd, &tlength, sizeof(int32_t));
        write(client_fd, &temp, sizeof(char) * length);
        
        printf("%s\n", temp);
    }
    printf("closing\n");
    close(client_fd);
    free(args);
    pthread_exit(NULL);

}

void init_server(char * ip, int port){
    printf("%s:%d\n",ip,port);
    int i;
    int j;
    FILE * fp = fopen("./ns.txt", "w");
    fprintf(fp, "%s:%d\n", ip, port);
    fclose(fp);

}
