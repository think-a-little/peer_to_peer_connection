#ifndef ZEROTYPEMESAGE_H
#define ZEROTYPEMESAGE_H
#include "protsrjdata.h"
#include <vector>
class ZeroTypeMesage : public ProtSRJData
{
public:
    void add_data(std::string data) override;
};

#endif // ZEROTYPEMESAGE_H
