#include "stabilization_system.h"

stabilization_system::stabilization_system(uint8_t x)
{
    source_code=x;
    send_fifth_type_message();
}
