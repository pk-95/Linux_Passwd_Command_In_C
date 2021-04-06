passwd:server.o client.o
	gcc server.o client.o
server.o:server.c server.h
	gcc -c server.c
client.c:client.c server.h
	gcc -c client.c
