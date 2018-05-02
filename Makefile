CLIENT = client.c start.c
SERVER = server.c TicketBooth.c regist.c

server:
	gcc -Wall $(SERVER) -o server

client:
	gcc -Wall $(CLIENT) -o client

debug server:
	gcc -g -Wall $(SERVER) -o server

debug client:
	gcc -g -Wall $(SERVER) -o client


clean server:
	rm server

clean client:
	rm client
