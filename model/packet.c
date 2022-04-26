#include <stdint.h>

// LEAP INDICATOR VALUES
#define LEAP_NO_WARNING 0x0
#define LEAP_PLUS_ONE 0x1
#define LEAP_MINUS_ONE 0x2
#define LEAP_UNDEFINED 0X3

// STATUS VALUES
#define STATUS_CLOCK_OK 0
#define STATUS_CARRIER_LOSS 1
#define STATUS_SYNCH_LOSS 2
#define STATUS_FORMAT_ERROR 3
#define STATUS_INTERFACE_OR_LINK_FAILURE 4

// REFERENCE CLOCK TYPE VALUES
#define REF_CLOCK_TYPE_UNSPECIFIED 0
#define REF_CLOCK_TYPE_PRIMARY 0
#define REF_CLOCK_TYPE_SECONDARY_INTERNET_HOST 0
#define REF_CLOCK_TYPE_SECONDARY_OTHER 0
#define REF_CLOCK_TYPE_EYEBALL 0

// TYPE OF CLOCK VALUES
#define CLOCK_TYPE_WWVB_RADIO "WWVB"
#define CLOCK_TYPE_GOES_SATELITE "GOES"
#define CLOCK_TYPE_WWV_RADIO "WWV"

struct packet {
    /*
     * 2 bits leap indicator
     * 6 bits status
     * 
     * LEAP INDICATOR
     * 00      no warning
     * 01      +1 second (following minute has 61 seconds)
     * 10      -1 second (following minute has 59 seconds)
     * 11      reserved for future use   
     * 
     * STATUS
     *    0       clock operating correctly
     *    1       carrier loss
     *    2       synch loss
     *    3       format error
     *    4       interface (Type 1) or link (Type 2) failure
     */
    uint8_t li_and_status;

    /*
     *    0       unspecified
     *    1       primary reference (e.g. radio clock)
     *    2       secondary reference using an Internet host via NTP
     *    3       secondary reference using some other host or protocol
     *    4       eyeball-and-wristwatch
     *    (additional codes reserved for future use)
     */
    uint8_t reference_clock_type;
    
    // precision of local clock in seconds to nearest powerr of two
    uint16_t precision;
    
    // estimated error of local clock
    uint32_t estimated_error;

    // estimated drift rate of local clock
    uint32_t estimated_drift_rate;

    /*
     * string defining type of clock
     * WWVB    WWVB radio clock (60 KHz)
     * GOES    GOES satellite clock (468 HMz)
     * WWV     WWV radio clock (2.5/5/10/15/20 MHz)
     * (and others as necessary)
     */
    uint32_t reference_clock_id;

    /*
     * timestamps to calculate error
     *
     * NTP timestamps are represented as a 64-bit fixed-point number, in
     * seconds relative to 0000 UT on 1 January 1900
     * 
     * The integer part is
     * in the first 32 bits and the fraction part in the last 32 bits
     */ 
    uint64_t reference_timestamp;
    uint64_t originate_timestamp;
    uint64_t receive_timestamp;
    uint64_t transmit_timestamp;
};

typedef struct packet NTPPacket;


/* 
 * Function to build the binary for the li_and_status member of the packet
 * 
 * @Param link_indicator: binary value containing only the link indicator value
 * 
 * @Param status: binary value containing only the status information
 * 
 * @Return: Two values mounted according to the spec
 */
uint8_t build_li_and_status(uint8_t link_indicator, uint8_t status) {
    uint8_t li_and_status_result = link_indicator << 6;
    return li_and_status_result | status;
}