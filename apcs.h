#ifndef APCS_H
#define APCS_H

#include "system.h"

class APCS : public system, public QMainWindow
{
private:
    int flight_type;
    int flight_number;
    int cycle_number;
    int segment_number;
    bool reciveDo=true, sendDo;
public:
    APCS(QWidget *parent);
    APCS(int flight_type, int flight_number, int cycle_number, int segment_number); // первый параметр в шарпах почему-то строка

    void receive();
    void send(std::string message);
    void func();
};

#endif // APCS_H
