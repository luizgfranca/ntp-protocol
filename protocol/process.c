#include "../model/packet.c"
#include <time.h>

uint64_t get_current_timestamp() {
    unsigned unix_timestamp = time(NULL);
    uint64_t unix_timestamp_64 = unix_timestamp;
    return unix_timestamp_64 << 32;
}

void process_ntp_request(NTPPacket* request) {
    uint64_t current_timestamp = get_current_timestamp();
    request->receive_timestamp = current_timestamp;
    request->originate_timestamp = current_timestamp;
    request->transmit_timestamp = current_timestamp;
}