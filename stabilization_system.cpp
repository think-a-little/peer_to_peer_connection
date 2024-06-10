#include "stabilization_system.h"

stabilization_system::stabilization_system(uint8_t x)
{
    source_code=SYSTEM_OF_STABILIZATION;
    send_fifth_type_message();
}
