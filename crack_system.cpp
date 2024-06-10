#include "crack_system.h"

crack_system::crack_system(uint8_t x)
{
    source_code=RBORDER_SUBSYSTEM_REGISTER_CRACK;
    send_fifth_type_message();
}
