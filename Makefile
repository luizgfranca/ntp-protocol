CC = g++
CFLAGS = -Wall -g 
OUTPATH = out

RUN_SERVER = ./out/server

server:
	$(CC) $(CFLAGS) -o $(OUTPATH)/server server.c
	$(RUN_SERVER)

clear:
	rm -rf out/*