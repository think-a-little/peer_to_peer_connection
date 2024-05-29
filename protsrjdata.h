#ifndef PROTSRJDATA_H
#define PROTSRJDATA_H
#include <vector>
#include<cstdint>
#include <string>
class ProtSRJData
{
public:
    std::vector<uint8_t> message_data;

    virtual void add_data(std::string data);
    virtual void add_data(std::vector<uint8_t> data);
    virtual std::vector<char> parse_data();
    virtual std::vector<uint8_t> get_data();
};

#endif // PROTSRJDATA_H
