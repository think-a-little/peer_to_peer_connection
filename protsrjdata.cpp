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
