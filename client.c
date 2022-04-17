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
    struct sockaddr_in server_addr;
    char message[32];

    strcpy(message, "hi from client");

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        perror("error openning socket\n");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    int size = sendto(
        sockfd, 
        message, 
        strlen(message) + 1, 
        MSG_CONFIRM,
        (const struct sockaddr *) &server_addr,
        sizeof(server_addr)
    );

    printf("message sent: %d bytes\n", size);

    return 0;
}