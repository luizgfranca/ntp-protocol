#include "network/request.h"
#include <string.h>
#include "./network/request.h"
#include "./model/packet.c"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    static char uri[255];

    strcpy(uri, "127.0.0.1");

    NTPPacket ntp_data;
    NTPPacket__initialize(&ntp_data);

    ntp_data.li_and_status = build_li_and_status(LEAP_PLUS_ONE, STATUS_CARRIER_LOSS);
    ntp_data.reference_clock_type = REF_CLOCK_TYPE_SECONDARY_INTERNET_HOST;
    ntp_data.precision = 0;
    ntp_data.estimated_error = 0;
    ntp_data.estimated_drift_rate = 0;
    strcpy(ntp_data.reference_clock_id, CLOCK_TYPE_WWV_RADIO);
    
    NTPPacket__print(ntp_data);

    char* content = (char*) &ntp_data;
    send_udp_request(
        uri, 
        3000, 
        content,
        sizeof(NTPPacket)
    );

    return 0;
}