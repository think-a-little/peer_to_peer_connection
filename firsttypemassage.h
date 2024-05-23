#ifndef FIRSTTYPEMASSAGE_H
#define FIRSTTYPEMASSAGE_H
#include "protsrjdata.h"
#include<stdexcept>
#include<cstdint>
#include<vector>
class FirstTypeMassage:ProtSRJData
{
private:
public:
    void add_data(std::vector<char> data) override;

};
#endif // FIRSTTYPEMASSAGE_H
