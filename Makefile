
CC = gcc

client1-lpc:
	gcc client1.c matrix.c -std=c99 -o client1-lpc -g -w

client2-lpc:
	gcc client2.c matrix.c -std=c99 -o client2-lpc -g -w

client3-lpc:
	gcc client3.c matrix.c -std=c99 -o client3-lpc -g -w

echo-server:
	gcc server.c echo-stub.c -o echo-server -g -pthread -w

mult-serv:
	gcc server.c mult-stub.c matrix.c -pthread -o mult-serv -g -std=c99 -w

client1-rpc:
	gcc client1.c client-stub.c -o client1-rpc -g -w

client2-rpc:
	gcc client2.c client-stub.c -g -o client2-rpc -w

sort-serv:
	gcc server.c sort-serv.c matrix.c -pthread -o sort-serv -g -w

min-serv:
	gcc server.c min-stub.c matrix.c -pthread -g -o min-serv -w

max-serv:
	gcc server.c max-stub.c matrix.c -pthread -g -o max-serv -w

client3-rpc:
	gcc client3.c client-stub.c -g -o client3-rpc -w

name-serv:
	gcc name-stub.c server.c -pthread -g -o name-serv -w
