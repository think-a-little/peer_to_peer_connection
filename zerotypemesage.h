#ifndef ZEROTYPEMESAGE_H
#define ZEROTYPEMESAGE_H
#include "protsrjdata.h"
#include <vector>
class ZeroTypeMesage : public ProtSRJData
{
public:
    void add_data(std::vector<char> data) override;
};

#endif // ZEROTYPEMESAGE_H
