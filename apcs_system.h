#ifndef APCS_SYSTEM_H
#define APCS_SYSTEM_H

#include "system.h"

class apcs_system :public system
{
private:
    int flight_type;
    int flight_number;
    int cycle_number;
    int segment_number;
    bool reciveDo=true, sendDo;
public:
    explicit apcs_system(QObject *parent = nullptr);
    apcs_system(int flight_type, int flight_number, int cycle_number, int segment_number); // первый параметр в шарпах почему-то строка
    ~apcs_system();

    void receive() override;
    void send(std::string message) override;
    void func();
};

#endif // APCS_H
