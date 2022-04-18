/*
 * Sends UDP datagram to the address and port defined,
 * with the message
 * 
 * @param null_terminated_address: Destination address
 *        with a null character at the end of the string
 * 
 * @param port: Destination port
 * 
 * @param message: Data to be sent
 * 
 * @param message_length: Length in bytes of the data
 *        of the message parameter
 * 
 * @return <= 0 if failed,
 *            transmitted bytes if success 
 */
int send_udp_request(
    char * null_terminated_address, 
    int port, 
    void * message, 
    int message_length
);