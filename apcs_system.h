#ifndef APCS_H
#define APCS_H

#include "system.h"

class apcs_system : system
{
private:
    int flight_type;
    int flight_number;
    int cycle_number;
    int segment_number;
    bool reciveDo=true, sendDo;
public:
    apcs_system(int flight_type, int flight_number, int cycle_number, int segment_number); // первый параметр в шарпах почему-то строка

    void receive() override;
    void send(std::string message) override;
    void func();
};

#endif // APCS_H
