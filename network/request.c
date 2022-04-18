#include "request.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>

int send_udp_request(
    char * null_terminated_address, 
    int port, 
    void * message, 
    int message_length
) {
    /*
     * socket openning
     * AF_INET: IPV4
     * SOCK_DGRAM: uses datagrams (UDP)
     */
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(socket_fd < 0) {
        printf("error openning socket\n");
        return -1;
    }

    //struct with network information of the destinatary
    struct sockaddr_in destinatary;
    
    // Address used is IPV4
    destinatary.sin_family = AF_INET; 

    // Converts address string to identifier, and sets it
    destinatary.sin_addr.s_addr = inet_addr(null_terminated_address);

    destinatary.sin_port = htons(port);

    
    // sends of message with information to the destinatary
    // with the described information 
    int sent_length = sendto(
        socket_fd,
        message,
        message_length + 1,
        MSG_CONFIRM,
        (const struct sockaddr *) &destinatary,
        sizeof(destinatary)
    );

    return sent_length;
}