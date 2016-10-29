// author: Charles Smith <cas275@pitt.edu>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void register_fun(int fun, char * ip, int port){
    // TODO get IP from sever
    int ns_port = 54438;
    char * ns_ip = NULL;
    
    FILE * fp;
    char * line = NULL;
    char ns_str[256];
    size_t len;

    fp = fopen("./ns.txt", "r");
    getline(&line, &len, fp);
    strncpy(ns_str, line,255);
    ns_str[255]='\0';
    ns_ip = strtok(ns_str,":");
    if(ns_ip == NULL){
        printf("ns_ip is NULL\n");
        return;
    }
    char * tmp = strtok(NULL, "");
    ns_port = atoi(tmp);
    close(fp);

    char str[50];
    sprintf(str, "%s:%d", ip, port);
    int32_t length = strlen(str);


    int sockfd;
    struct sockaddr_in serv;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv, sizeof(struct sockaddr_in));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(ns_port);

    inet_pton(AF_INET, ns_ip, &(serv.sin_addr));
    connect(sockfd, (struct sockaddr *) &serv, sizeof(struct sockaddr_in));

    uint32_t tid;
    time_t ti;
    srand((unsigned)time(&ti));
    tid = rand();

    tid = htonl(tid);
    write(sockfd, &(tid), sizeof(int32_t));


    int32_t reg = 0;
    reg = htonl(reg);
    write(sockfd, &reg, sizeof(int32_t));

    int32_t function_num = fun;
    function_num = htonl(function_num);
    write(sockfd, &function_num, sizeof(int32_t));

    write(sockfd, &length, sizeof(int32_t));
    write(sockfd, &str, sizeof(char)*length);
}
