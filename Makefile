
CC = gcc

name_server: name_server.c
	gcc -o name_server name_server.c -g

client1-lpc:
	gcc client1.c matrix.c -std=c99 -o client1-lpc -g

client2-lpc:
	gcc client2.c matrix.c -std=c99 -o client2-lpc -g

client3-lpc:
	gcc client3.c matrix.c -std=c99 -o client3-lpc -g

echo-server:
	gcc server.c echo-stub.c -o echo-server -g -pthread

mult-serv:
	gcc server.c mult-stub.c matrix.c -pthread -o mult-serv -g -std=c99

client1-rpc:
	gcc client1.c client-stub.c -o client1-rpc -g

client2-rpc:
	gcc client2.c client-stub.c -g -o client2-rpc

sort-serv:
	gcc server.c sort-serv.c matrix.c -pthread -o sort-serv -g

min-serv:
	gcc server.c min-stub.c matrix.c -pthread -g -o min-serv

max-serv:
	gcc server.c max-stub.c matrix.c -pthread -g -o max-serv

client3-rpc:
	gcc client3.c client-stub.c -g -o client3-rpc

