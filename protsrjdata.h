#ifndef PROTSRJDATA_H
#define PROTSRJDATA_H
#include <vector>
#include<cstdint>
class ProtSRJData
{
public:
    std::vector<uint8_t> message_data;

    virtual void add_data(std::vector<char> data)=0;
    virtual void add_data(std::vector<uint8_t> data)=0;
    virtual std::vector<char> parse_data()=0;
    virtual std::vector<uint8_t> get_data()=0;
};

#endif // PROTSRJDATA_H
