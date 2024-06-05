#include "fourthtypemessage.h"
#include <vector>
#include<stdexcept>
void FourthTypeMessage:: add_data(std::string data) {
    if (!data.empty()) {
              throw std::runtime_error("Data is not empty in fourth type message");
          }
          char message_data[1];
          message_data[0] = '-';
};
void FourthTypeMessage:: add_data(std::vector<uint8_t> data){
    message_data.clear();
};
std::vector<char> FourthTypeMessage::parse_data(){
    std::vector<char> nothing;
    return nothing;
}
