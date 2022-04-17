CC = g++
CFLAGS = -Wall -g 
OUTPATH = out

RUN_SERVER = ./out/server
RUN_CLIENT = ./out/client

server:
	$(CC) $(CFLAGS) -o $(OUTPATH)/server server.c
	$(RUN_SERVER)

client:
	$(CC) $(CFLAGS) -o $(OUTPATH)/client client.c
	$(RUN_CLIENT)

clear:
	rm -rf out/*