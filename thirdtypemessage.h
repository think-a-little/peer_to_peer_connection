#ifndef THIRDTYPEMESSAGE_H
#define THIRDTYPEMESSAGE_H
#include "protsrjdata.h"

class ThirdTypeMessage:ProtSRJData
{
public:
    void add_data(std::vector<char> data) override;

};

#endif // THIRDTYPEMESSAGE_H
