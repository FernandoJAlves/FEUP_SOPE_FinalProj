CLIENT = client.c cregist.c
SERVER = server.c TicketBooth.c sregist.c Seat.c

server:
	gcc -Wall $(SERVER) -o server

client:
	gcc -Wall $(CLIENT) -o client

start:
	gcc -Wall start.c -o start

debugs:
	gcc -g -Wall $(SERVER) -o server

debugc:
	gcc -g -Wall $(SERVER) -o client


cleans:
	rm server

cleanc:
	rm client
