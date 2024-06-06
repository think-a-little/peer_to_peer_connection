#include "apcs_system.h"

apcs_system::apcs_system(int flight_type, int flight_number, int cycle_number, int segment_number) :
    flight_type(flight_type),
    flight_number(flight_number),
    cycle_number(cycle_number),
segment_number(segment_number) {
    source_code=APCS;
    send_fifth_type_message();
}

QString apcs_system::recieve(QString msg)
{

}

