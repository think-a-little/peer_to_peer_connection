#include "fifthtypemessage.h"
#include <vector>
#include<stdexcept>
void FifthTypeMessage:: add_data(std::string data) {
    if (!data.empty()) {
              throw std::runtime_error("Data is not empty in fifth type message");
          }

          char message_data[1];
          message_data[0] = '-';
};
void FifthTypeMessage:: add_data(std::vector<uint8_t> data){
    message_data.clear();
};
std::vector<char> FifthTypeMessage::parse_data(){
    std::vector<char> nothing;
    return nothing;
}

