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

int main(){
    
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
    int clilen = sizeof(client);

    int client_sock_fd = accept(sock_fd, (struct sockaddr *) &client, &clilen);
    if( client_sock_fd < 0){
        printf("could not accept connection, returned: %d\n", client_sock_fd);
    }
    printf("accepted\n");
    
    
    // read the message
    char buffer[256];
    bzero(buffer, 256);

    res = read(client_sock_fd, buffer, 255);
    if(res < 0){
        printf("read error from client, returned: %d\n", res);
    }
    else{
        printf("message:\n%s\n", buffer);
    }

    
    // TODO: process message
    

    // send back either success or error message
    
    res = write(client_sock_fd, "success", 8);
    if(res < 0){
        printf("could not send message to client\n");
    }

    return 0;
}

