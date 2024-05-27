#include "protsrjdata.h"
#include <vector>
#include <stdexcept>
#include <string>
#include <cstddef> // Для std::size_t
void ProtSRJData:: add_data(std::vector<uint8_t> data) {
        message_data.assign(data.begin(), data.end());
}
std::vector<uint8_t> ProtSRJData:: get_data(){
    return message_data;
} ;
std::vector<char> ProtSRJData:: parse_data() {
    std::vector<char> parsed_data(message_data.size());
            for (ssize_t i = 0; i < message_data.size(); ++i) {
                parsed_data[i] = static_cast<char>(message_data[i]); // Приведение uint8_t к char
            }

            return parsed_data;
};
void ProtSRJData::add_data(std::vector<char> data){
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
}
