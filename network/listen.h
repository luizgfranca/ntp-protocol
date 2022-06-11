typedef struct request_message {
    void* buffer;
    int length;
} RequestMessage;

RequestMessage* udp_listen(int port, void (*callback)(RequestMessage*)) ;