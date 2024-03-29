// Author: Charles Smith <cas275@pitt.edu>
// FOR: CS2510
//
// port mapping application for project 1
// usage: ./name_server

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>


#define OUT_FILE "ns.txt"
#define CACHE_SIZE 20
#define FUNCTIONS 4
#define MAX_SERVERS 5


//globals
int cache[CACHE_SIZE][2]; // format cache[x][0] = tranID
                          //        cache[x][1] = process_message result
int cache_ptr = 0;
struct sockaddr_in reg[FUNCTIONS][MAX_SERVERS];


// process requests to register/unregister a service
//
// messages are passed as strings, so that this program
// doesn't need changed every time the set of functions changes
int process_message(char* buf){
    char* buffer;
    buffer = strndup(buf,255);

    // TODO
    // check if message is a duplicate 
    // check if server is already registered/unregistered
    // return 0 on success 
    // return prev result on dup
    // return -1 on invalid


    //get the tid (transaction id)
    char * tid_str = strtok(buffer,"-");

    if (tid_str == NULL){
        printf("invalid tid\n");
        free(buffer);
        return -1;
    }

    int tid = atoi(tid_str);
    if(tid <= 0){
        printf("%s is not a valid TID\n", tid_str);
        free(buffer);
        return -1;
    }
    printf("TID: %d\n", tid);


    // check cache
    int i;
    for(i=0; i<CACHE_SIZE; i++){
        if(cache[i][0] == tid){ //tid exists in cache
            printf("tid in cache, prev result: %d\n", cache[i][1]);
            free(buffer);
            return cache[i][1];
        }
    }
    printf("not found in cache\n");


    // find what type we're doing
    char * type = strtok(NULL, "-");
    if(type == NULL){
        printf("Invalid type\n");
        return -1;
    }
    printf("type = %s\n", type);


    if(type == "cli"){
        printf("client\n");
        

    }
    else if(type == "rem"){
        printf("remove request\n");
    }
    else if(type == "reg"){
        printf("register request\n");

        //find out the client's location
        char * client_ip = strtok(NULL, ":");
        if(client_ip == NULL){
            printf("invalid client IP\n");
            // TODO update cache
            free(buffer);
            return -1;
        }
        printf("recieved %s as client IP\n", client_ip);

        struct in_addr client_addr;
        if(!inet_aton(client_ip, &client_addr)){ // returns non-zero if client_ip is invalid
            printf("client ip: %s was found to be invalid by inet_aton\n",client_ip);
            free(buffer);
            // TODO update cache
            return -1;
        }
        printf("client addr stored as %u\n", client_addr.s_addr);

        char * client_port_str = strtok(NULL, "-");
        if(client_port_str == NULL){
            printf("invalid port\n");
            // TODO update cache
            free(buffer);
            return -1;
        }
        printf("got %s as client port number\n", client_port_str);
        unsigned short client_port = atoi(client_port_str);
        if(client_port == 0){
            printf("%s could not be converted into an unsigned short\n", client_port_str);
            free(buffer);
            //TODO update cache
            return -1;
        }
        printf("client port stored as %u\n", client_port);


    }
    free(buffer);
    return 0;

}


int main(){

    bzero(cache,sizeof(int)*40); //clear cache


    //create the socket file descripter 
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd <0){
        printf("Unable to create the socket, returned: %d\n", sock_fd);
        exit(1);
    }
    printf("created socket\n");


    //bind the socket
    struct sockaddr_in serv;
    bzero( (char *) &serv, sizeof(serv)); // set to 0

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr   = INADDR_ANY;
    serv.sin_port   = 0;

    int res = bind(sock_fd, (struct sockaddr *) &serv, sizeof(serv));

    if(res < 0){
        printf("unable to bind, returned: %d\n", res);
        exit(1);
    }
    printf("bound socket\n");

    // find what port/IP/etc. we're at
    struct sockaddr_in test;
    int len = sizeof(test);
    int len2 = len;
    int failed = 0;

    res = getsockname(sock_fd, (struct sockaddr *) &test, &len);

    if(res < 0){
        printf("cannot getsockname(), returned: %d\n", res);
        failed = 1;
    }

    if(len > len2){
        printf("getsockname returned an unexpectedly large struct\nexpected: %d\ngot: %d\n",len, len2);
        failed = 1;
    }

    if(failed){
        exit(1);
    }


    // print results
    printf("port: %d\n", ntohs(test.sin_port));
    printf("IP: %s\n", inet_ntoa(test.sin_addr));


    //save results
    FILE * out;
    out = fopen(OUT_FILE, "w");
    fprintf(out, "%s:%d\n", inet_ntoa(test.sin_addr), ntohs(test.sin_port));
    fclose(out);
    printf("saved\n");


    //start listening --Important part
    res = listen(sock_fd, 5); //listen, with at most 5 in queue.  
    if(res < 0){
        printf("could not listen, returned: %d\n", res);
        exit(1);
    }
    printf("listening\n");


    //accepting connections
    //TODO: repeat forever
    struct sockaddr_in client;
    int clilen;
    char buffer[256];
    int client_sock_fd;

    while(1){
        clilen = sizeof(client);

        client_sock_fd = accept(sock_fd, (struct sockaddr *) &client, &clilen);
        if( client_sock_fd < 0){
            printf("could not accept connection, returned: %d\n", client_sock_fd);
        }
        printf("accepted\n");


        // read the message
        bzero(buffer, 256);

        res = read(client_sock_fd, buffer, 255);
        if(res < 0){
            printf("read error from client, returned: %d\n", res);
        }
        else{
            printf("message:\n%s\n", buffer);
        }


        // proccess
        res = process_message(buffer);

        // return results
        if (res < 0){
            res = write(client_sock_fd, "failed ", 8);
            if(res < 0){
                printf("could not send message to client\n");
            }
        }
        else{
            res = write(client_sock_fd, "success", 8);
            if(res < 0){
                printf("could not send message to client\n");
            }
        }


        close(client_sock_fd);
    }
    return 0;
}

