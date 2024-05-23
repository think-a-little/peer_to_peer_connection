#ifndef FOURTHTYPEMESSAGE_H
#define FOURTHTYPEMESSAGE_H
#include "protsrjdata.h"

class FourthTypeMessage : public ProtSRJData
{
public:
    void add_data(std::vector<char> data) override;
    void add_data(std::vector<uint8_t> data) override;
    std::vector<char> parse_data() override;
};

#endif // FOURTHTYPEMESSAGE_H
