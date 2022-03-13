#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3000
#define MSG_SIZE 1024

int main(int argc, char *argv[]) {
    printf("Initializing...\n");
    struct sockaddr_in address;
    struct hostent *gethostbyname();
    char message[MSG_SIZE];
    int msg_length = 0;

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        perror("error openning socket\n");
        exit(1);
    }

    bzero((char *) &address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORT);

    if(bind(sock, (struct sockaddr *) &address, sizeof(address))) {
        perror("error on binding");
        exit(0);
    }

    printf("listening to port %d\n", ntohs(address.sin_port));

    while (1 == 1) {
        msg_length = read(sock, message, MSG_SIZE);
        printf("\nmessage received: length %d\n", msg_length);
        if(msg_length > 0) {
            printf("%s\n", message);    
        }
    }

    return 0;
}