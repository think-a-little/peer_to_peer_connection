#ifndef APCS_H
#define APCS_H

#include "model.h"

class APCS : Model
{
private:
    int flight_type;
    int flight_number;
    int cycle_number;
    int segment_number;
public:
    APCS(int, int, int, int); // первый параметр в шарпах почему-то строка
};

#endif // APCS_H
