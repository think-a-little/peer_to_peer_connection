#include "firsttypemassage.h"
#include <vector>
#include <stdexcept>
#include <string>
#include <cstddef> // Для std::size_t
void FirstTypeMassage:: add_data(std::string data){
    if (data.empty()) {
        throw std::runtime_error("Data is null in first type message");
    }
    std::vector<uint8_t> message_data(data.size());

    for (ssize_t i = 0; i < data.size(); ++i) {
        if (data[i] < '0' || data[i] > '6') {
            throw std::runtime_error("State of channel is invalid in first type message");
        }
        message_data[i] = static_cast<uint8_t>(data[i]); // Приведение char к uint8_t
    }

    // Здесь можно продолжить работу с message_data...
}



