#ifndef FIFTHTYPEMESSAGE_H
#define FIFTHTYPEMESSAGE_H
#include"protsrjdata.h"
class FifthTypeMessage : public ProtSRJData
{
public:
    void add_data(std::vector<char> data) override;
    void add_data(std::vector<uint8_t> data) override;
    std::vector<char> parse_data() override;
};

#endif // FIFTHTYPEMESSAGE_H
