
CC = gcc

name_server: name_server.c
	gcc -o name_server name_server.c -g

client1-lpc:
	gcc client1.c matrix.c -std=c99 -o client1-lpc -g

client2-lpc:
	gcc client2.c matrix.c -std=c99 -o client2-lpc -g

client3-lpc:
	gcc client3.c matrix.c -std=c99 -o client3-lpc -g

