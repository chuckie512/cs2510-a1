// author: Charles Smith <cas275@pitt.edu>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>


// read ns.txt to get the IP/port
int get_serv(int func, char ** IP, int * PORT){
//    FILE * fp;
//    char * line = NULL;
//    char str[256];
//    char * function;
//    char * p;
//    size_t len;
//
//    fp = fopen("./ns.txt", "r");
//
//    while(getline(&line, &len, fp) != -1){
//        strncpy(str, line, 255);
//        str[255] = '\0';
//        function = strtok(str, " ");
//        if(function != NULL){
//            if(atoi(function) == func){
//                *IP = strtok(NULL,":");
//                *PORT = atoi(strtok(NULL, ""));
//                fclose(fp);
//                return 0;
//            }
//        }
//    }
//    fclose(fp);
//    return -1;

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

    int32_t req = 1;
    req = htonl(req);
    write(sockfd, &req, sizeof(int32_t));
   
    int32_t fun = (int32_t)func;
    fun = htonl(fun);
    write(sockfd, &fun, sizeof(int32_t));

    int32_t length = 0;
    read(sockfd, &length, sizeof(int32_t));
    length = ntohl(length);

    char res[256];
    bzero(res, 256);
    read(sockfd, &res, 255);
    res[255] = '\0';

    *IP = strtok(res, ":");
    *PORT = atoi(strtok(NULL, ""));
    return 0;


}


void multiply(int32_t n, int32_t m, int32_t l, int32_t a[n][m], int32_t b[m][l], int32_t c[n][l]){

    // TODO get ip & port

    char * IP[50];
    int PORT;

    get_serv(1, &IP, &PORT);

    int sockfd;
    struct sockaddr_in serv;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv, sizeof(struct sockaddr_in));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);

    inet_pton(AF_INET, IP, &(serv.sin_addr));

    connect(sockfd, (struct sockaddr *) &serv, sizeof(struct sockaddr_in));

    uint32_t tid;
    time_t ti;
    srand((unsigned)time(&ti));
    tid = rand();

    tid = htonl(tid);
    write(sockfd, &(tid), sizeof(uint32_t));

    int32_t temp;

    temp=htonl(n);
    write(sockfd, &(temp), sizeof(int32_t));
    temp=htonl(m);
    write(sockfd, &(temp), sizeof(int32_t));
    temp=htonl(l);
    write(sockfd, &(temp), sizeof(int32_t));

    // send matrix
    int i;
    int j;
    for(i=0; i<n; i++){
        for(j=0; j<m; j++){
            temp = htonl(a[i][j]);
            write(sockfd, &temp, sizeof(int32_t));
        }
    }

    for(i=0; i<m; i++){
        for(j=0; j<l; j++){
            temp = htonl(b[i][j]);
            write(sockfd, &temp, sizeof(int32_t));
        }
    }

    // get results
    for(i=0; i<n; i++){
        for(j=0; j<l; j++){
            read(sockfd, &c[i][j], sizeof(int32_t));
            c[i][j] = ntohl(c[i][j]);
        }
    }

}


void sort(int32_t n, int32_t a[n]){

    char * IP[50]; 
    int PORT;

    get_serv(2, &IP, &PORT);


    int sockfd;
    struct sockaddr_in serv;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv, sizeof(struct sockaddr_in)); 

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);

    inet_pton(AF_INET, IP, &(serv.sin_addr));

    connect(sockfd, (struct sockaddr *) &serv, sizeof(struct sockaddr_in));

    uint32_t tid;
    time_t ti;
    srand((unsigned)time(&ti));
    tid = rand();

    tid = htonl(tid);
    write(sockfd, &(tid), sizeof(int32_t));

    int32_t temp;
    temp = htonl(n);
    write(sockfd, &temp, sizeof(int32_t));

    int i;
    for(i=0; i<n; i++){
        temp = htonl(a[i]);
        write(sockfd, &temp, sizeof(int32_t));
    }

    for(i=0; i<n; i++){
        read(sockfd, &temp, sizeof(int32_t));
        a[i] = ntohl(temp);
    }

}

int32_t min(int32_t n, int32_t a[n]){

    char * IP[50]; 
    int PORT;

    get_serv(3, &IP, &PORT);


    int sockfd;
    struct sockaddr_in serv;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv, sizeof(struct sockaddr_in));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);

    inet_pton(AF_INET, IP, &(serv.sin_addr));

    connect(sockfd, (struct sockaddr *) &serv, sizeof(struct sockaddr_in));

    uint32_t tid;
    time_t ti;
    srand((unsigned)time(&ti));
    tid = rand();

    tid = htonl(tid);
    write(sockfd, &(tid), sizeof(int32_t));

    int32_t temp;
    temp = htonl(n);
    write(sockfd, &temp, sizeof(int32_t));

    int i;
    for(i=0; i<n; i++){
        temp = htonl(a[i]);
        write(sockfd, &temp, sizeof(int32_t));
    }

    read(sockfd, &temp, sizeof(int32_t));
    temp = ntohl(temp);
    return temp;

}

int32_t max(int32_t n, int32_t a[n]){

    char * IP[50]; 
    int PORT;

    get_serv(4, &IP, &PORT);

    int sockfd;
    struct sockaddr_in serv;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv, sizeof(struct sockaddr_in));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);

    inet_pton(AF_INET, IP, &(serv.sin_addr));

    connect(sockfd, (struct sockaddr *) &serv, sizeof(struct sockaddr_in));

    uint32_t tid;
    time_t ti;
    srand((unsigned)time(&ti));
    tid = rand();

    tid = htonl(tid);
    write(sockfd, &(tid), sizeof(int32_t));

    int32_t temp;
    temp = htonl(n);
    write(sockfd, &temp, sizeof(int32_t));

    int i;
    for(i=0; i<n; i++){
        temp = htonl(a[i]);
        write(sockfd, &temp, sizeof(int32_t));
    }

    read(sockfd, &temp, sizeof(int32_t));
    temp = ntohl(temp);
    return temp;
}

