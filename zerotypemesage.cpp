#include "zerotypemesage.h"
#include <stdexcept>
void ZeroTypeMesage::add_data(std::vector<char> data){
    if (data.empty()){
        message_data.resize(1);
        message_data[0]='-';
        return;
    }
    if (sizeof (data)<10)
        throw std::runtime_error("Data is invalid in zero type");
    message_data.resize(sizeof (data));
    int counter_delimetr=0;
    for (int i=0;i<sizeof (data);i++){
        if (data[i]==';') counter_delimetr++;
        message_data[i] = data[i];
    }
    if (counter_delimetr!=5)
        throw std::runtime_error("Data is invalid in zero type message. Data has "
                                 +std::to_string( counter_delimetr) +
                                 " fields");
}
