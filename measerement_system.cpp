#include "measerement_system.h"

measerement_system::measerement_system(uint8_t source_code)
{
    this->source_code=SYSTEM_MEASUREMENT_MOVEMENT;
    send_fifth_type_message();
}
