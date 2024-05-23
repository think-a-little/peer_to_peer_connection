#include "secondtypemessage.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstddef> // Для std::size_t

void SecondTypeMessage::add_data(std::vector<char> data){
    if (data.empty()) {
        throw std::runtime_error("Data is null in second type message");
    }
    std::vector<uint8_t> message_data(data.size());

    for (ssize_t i = 0; i < data.size(); ++i) {
        message_data[i] = static_cast<uint8_t>(data[i]); // Приведение char к uint8_t
    }


}
