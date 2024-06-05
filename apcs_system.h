#ifndef APCS_SYSTEM_H
#define APCS_SYSTEM_H

#include "system.h"
#include "srj_consts.h"
class apcs_system : public system
{
private:
    int flight_type;
    int flight_number;
    int cycle_number;
    int segment_number;
    bool reciveDo=true, sendDo;
public:
    apcs_system(int flight_type, int flight_number, int cycle_number, int segment_number); // первый параметр в шарпах почему-то строка
    ~apcs_system();
    void func();

};

#endif // APCS_H
