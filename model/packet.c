#include <stdint.h>

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
    
    // estimated erro of local clock
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
     */ 
    uint64_t reference_timestamp;
    uint64_t originate_timestamp;
    uint64_t receive_timestamp;
    uint64_t transmit_timestamp;
};