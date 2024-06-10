#include "system_dist.h"

system_dist::system_dist(uint8_t source_code)
{
    this->source_code=LBORDER_SUBSYSTEM_DIST_VIS_WATCH;
    send_fifth_type_message();
}
