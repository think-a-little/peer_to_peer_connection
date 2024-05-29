#ifndef FIRSTTYPEMASSAGE_H
#define FIRSTTYPEMASSAGE_H
#include "protsrjdata.h"
#include<stdexcept>
#include<cstdint>
#include<vector>
class FirstTypeMassage:public ProtSRJData
{
public:
    std::vector<uint8_t> message_data;
    void add_data(std::string data) override;

};
#endif // FIRSTTYPEMASSAGE_H
