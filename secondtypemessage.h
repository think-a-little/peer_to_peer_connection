#ifndef SECONDTYPEMESSAGE_H
#define SECONDTYPEMESSAGE_H
#include "protsrjdata.h"

class SecondTypeMessage : public ProtSRJData
{
public:
    void add_data(std::vector<char> data) override;
};

#endif // SECONDTYPEMESSAGE_H
