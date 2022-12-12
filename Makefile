CC=gcc


EXEC = client server

all: $(EXEC)

client: client.c
	$(CC) -o client client.c

server: server.c
	$(CC) -o server server.c

clean:
	rm -f $(EXEC) *.o *~ core

