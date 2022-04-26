#include "network/request.h"
#include <string.h>
#include "./network/request.h"
#include "./model/packet.c"

int main(int argc, char *argv[]) {
    static char message[255];
    static char uri[255];

    strcpy(uri, "127.0.0.1");

    NTPPacket packet;
    memset(&packet, 0, sizeof(NTPPacket));
    packet.li_and_status = build_li_and_status(LEAP_PLUS_ONE, STATUS_CARRIER_LOSS);
    packet.reference_clock_type = REF_CLOCK_TYPE_SECONDARY_INTERNET_HOST;
    packet.precision = 0;
    packet.estimated_error = 0;
    packet.estimated_drift_rate = 0;
    packet.reference_clock_id = CLOCK_TYPE_WWV_RADIO;

    send_udp_request(uri, 3000, (void *) &packet, sizeof(NTPPacket));

    return 0;
}