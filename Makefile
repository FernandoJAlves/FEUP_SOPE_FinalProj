CLIENT = client.c 
SERVER = server.c TicketBooth.c regist.c

server:
	gcc -Wall $(SERVER) -o server

client:
	gcc -Wall $(CLIENT) -o client

debugs:
	gcc -g -Wall $(SERVER) -o server

debugc:
	gcc -g -Wall $(SERVER) -o client


cleans:
	rm server

cleanc:
	rm client
