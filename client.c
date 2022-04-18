#include "network/request.h"
#include <string.h>

int main(int argc, char *argv[]) {
    static char message[255];
    static char uri[255];

    strcpy(message, "Hello world");
    strcpy(uri, "127.0.0.1");

    send_udp_request(uri, 3000, (void *) message, strlen(message) + 1);

    return 0;
}