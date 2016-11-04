Author: Charles Smith
Pitt Email: CAS275@pitt.edu
Class: CS2510 Computer Operating Systems
Assignment: Project 1 Simple RPC

-------------------------------------------------------------------------------------------------------------------------------------
Source files:

matrix.c: 
    This file contains a simple matrix library

matrix.h: 
    This is a header file defining the operations in matrix.c

client1.c client2.c client3.c:
    These are simple example using the matrix library. It can be compiled either with
    the matrix.c file for local execution, or with the client-stub.c to implement the client 
    side of the RPCs.

client-stub.c:
    This implements the matrix.h functions as client-side RPCs.

server.h:
    A header file with the required server functions

server.c:
    This is an extremely simple threaded server that is used for all the servers in this project.
    The exact function of the server is changed based on how server.h is implemented for that particular server.

echo-stub.c:
    A test for the server.c, this is just to demostrate the use of server.c

max-stub.c:
    The server implentation for the MAX function call in the RPC

min-stub.c:
    The server implementation for the MIN function call in the RPC

mult-stub.c:
    The server implementation for the multiply function call in the RPC

sort-serv.c:
    The server implementation for the SORT function call in the RPC

name-stub.c:
    The server implementation for the name server (port mapper) in the RPC.  This must be started before the other
    servers.


------------------------------------------------------------------------------------------------------------------------
USAGE:




0) (run the make file)

FOR RPC:

1) start the name server/port mapper (this must be run in the same AFS directory as the other programs)
    ./name-serv

2) start the other servers you wish to use
    ./mult-serv
    ./sort-serv
    ./min-serv
    ./max-serv

3) run the rpc client programs
    ./client1-rpc
    ./client2-rpc
    ./client3-rpc

FOR LPC

1) run the lpc client programs
    ./client1-lpc
    ./client2-lpc
    ./client3-lpc

NOTE: as long as the required servers are running and can be found, rpc programs should produce the same results as the LPC
      versions.

----------------------------------------------------------------------------------------------------------------------------
KNOWN ISSUES:

 * CACHE is not implemented on the name-server, as implementation has shown it to be faster to just find the result again

 * CACHE is not implemented on functions returning an array 

 * RPC CLIENTS will not return any results if the name server cannot be reached 
 
 * The server currently only reports 0.0.0.0 as the IP address, so all programs must execute on the same machine 

 * When the name server has no server availible for a request, the client will crash

 * The name server does not perform a status check on the servers to see if they are still reachable, and may report
   old information to the clients


