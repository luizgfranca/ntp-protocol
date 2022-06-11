#include "listen.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_MSG_SIZE 1024
#define LOCAL_ADDRESS "127.0.0.1"

RequestMessage* udp_listen(int port, void (*callback)(RequestMessage*)) {
    struct sockaddr_in address;
    char message[MAX_MSG_SIZE];
    int received_received_msg_length = 0;


    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        perror("[udp_listen] error openning socket\n");
        exit(1);
    }

    bzero((char *) &address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(LOCAL_ADDRESS);
    address.sin_port = htons(port);

    if(bind(sock, (struct sockaddr *) &address, sizeof(address))) {
        perror("[udp_listen] could not bind to port");
        exit(1);
    }

    printf("[udp_listen] listening to port %d\n", ntohs(address.sin_port));

    while (1 == 1) {
        int received_msg_length = read(sock, message, MAX_MSG_SIZE);
        if(received_msg_length > 0) {
            static RequestMessage requestMessage;
            requestMessage.length = received_msg_length;
            requestMessage.buffer = (void *) message;
            if(callback != NULL) {
                callback(&requestMessage);
            }    
            // create thread to process message
        }
    }

    return 0;
}