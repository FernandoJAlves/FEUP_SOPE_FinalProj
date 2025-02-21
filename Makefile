CLIENT = client.c cregist.c request.c
SERVER = server.c TicketBooth.c sregist.c Seat.c request.c

all: server client

server:
	gcc -Wall $(SERVER) -o server -lpthread

client:
	gcc -Wall $(CLIENT) -o client -lpthread

debugs:
	gcc -g -Wall $(SERVER) -o server

debugc:
	gcc -g -Wall $(SERVER) -o client


clean:
	rm server
	rm client
