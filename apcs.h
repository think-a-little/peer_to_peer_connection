#ifndef APCS_H
#define APCS_H

#include "system.h"

class APCS : system
{
private:
    int flight_type;
    int flight_number;
    int cycle_number;
    int segment_number;
public:
    APCS(int flight_type, int flight_number, int cycle_number, int segment_number) : system(),
    flight_type(flight_type),
    flight_number(flight_number),
    cycle_number(cycle_number),
    segment_number(segment_number) {} // первый параметр в шарпах почему-то строка

    void receive() override;
    void send(std::string message) override;
    void func();
};

#endif // APCS_H
