#include "thirdtypemessage.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstddef> // Для std::size_t
#include "SRJ_Consts.cpp"

void ThirdTypeMessage::add_data(std::vector<char> data){
    if (data.empty()) {
                throw std::runtime_error("Data is null in third type message");
            }
            if (data.size()!= 3) {
                throw std::runtime_error("Data is invalid in third type message");
            }
            std::vector<uint8_t> message_data(data.size());

            for (ssize_t i = 0; i < data.size(); ++i) {
                message_data[i] = static_cast<uint8_t>(data[i]); // Приведение char к uint8_t
            }

            if (!check_source(message_data[0]))
                throw std::runtime_error("Source code is invalid in third type message ");
}
