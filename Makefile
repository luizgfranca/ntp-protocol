CC = g++
CFLAGS = -Wall -g 

OUT_PATH = out
NETWORK_PATH = network

RUN_SERVER = ./out/server
RUN_CLIENT = ./out/client


server:
	$(CC) $(CFLAGS) -o $(OUT_PATH)/server server.c
	$(RUN_SERVER)


client: network
	$(CC) $(CFLAGS) -c client.c -o $(OUT_PATH)/client.o
	$(CC) $(CFLAGS) -o $(OUT_PATH)/client \
		$(OUT_PATH)/client.o \
		$(OUT_PATH)/$(NETWORK_PATH)/request.o	
	$(RUN_CLIENT)


network: request listen

request:
	$(CC) $(CFLAGS) -c $(NETWORK_PATH)/request.c -o $(OUT_PATH)/$(NETWORK_PATH)/request.o 

request:
	$(CC) $(CFLAGS) -c $(NETWORK_PATH)/listen.c -o $(OUT_PATH)/$(NETWORK_PATH)/listen.o 


clear:
	rm -rf out/*