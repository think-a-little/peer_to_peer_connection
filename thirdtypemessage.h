#ifndef THIRDTYPEMESSAGE_H
#define THIRDTYPEMESSAGE_H
#include "protsrjdata.h"

class ThirdTypeMessage:public ProtSRJData
{
public:
    void add_data(std::string data) override;

};

#endif // THIRDTYPEMESSAGE_H
