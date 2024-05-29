#include "protsrj.h"
#include <vector>
#include <ctime>
#include <string>
#include <chrono>
#include "srj_consts.h"
#include "srj_consts.h"
#include "zerotypemesage.h"
#include "firsttypemassage.h"
#include "secondtypemessage.h"
#include "thirdtypemessage.h"
#include "fourthtypemessage.h"
#include "fifthtypemessage.h"
#include <sstream>
#include <QDebug>
SRJ_Consts checker;
ProtSRJ ProtSRJ::ProtSRJ_create(uint8_t source){
    ProtSRJ res;
    res.packet_source=source;
    res.send_date_and_time=create_date();

}
std::vector<uint8_t> ProtSRJ::create_date(){
    std::string date;
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&currentTime);

    std::ostringstream oss;
        oss.fill('0');
        oss.width(2);
    oss << std::to_string(timeInfo->tm_year-100);
    std::string year =oss.str();

    std::ostringstream oss1;
        oss1.fill('0');
        oss1.width(2);
    oss1 << std::to_string(timeInfo->tm_mon+1);
    std::string month = oss1.str();

    std::ostringstream oss2;
        oss2.fill('0');
        oss2.width(2);
    oss2 << std::to_string(timeInfo->tm_mday);
    std::string day = oss2.str();

    std::ostringstream oss3;
        oss3.fill('0');
        oss3.width(2);
    oss3 << std::to_string(timeInfo->tm_hour);
    std::string hour = oss3.str();

    std::ostringstream oss4;
        oss4.fill('0');
        oss4.width(2);
    oss4 << std::to_string(timeInfo->tm_min);
    std::string min = oss4.str();

    std::ostringstream oss5;
        oss5.fill('0');
        oss5.width(2);
    oss5 << std::to_string(timeInfo->tm_sec);
    std::string sec = oss5.str();

    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
    unsigned int milliseconds = static_cast<unsigned int>(duration.count()) / 1000;
    unsigned int roundedMilliseconds = milliseconds / 10;
    std::string milesecond = std::to_string(roundedMilliseconds);
    date=year+'/'+month+'/'+day+'-'+hour+':'+min+':'+sec+',';
    std::vector<uint8_t> res(date.begin(),date.end());
    return res;
}
ProtSRJ ProtSRJ::ProtSRJ_create(uint8_t source, std::vector<uint8_t> date_and_time){
    ProtSRJ res;
    res.packet_source=source;
    res.send_date_and_time=date_and_time;
    return res;
}
ProtSRJ ProtSRJ::parse_packet(std::vector<uint8_t> packet){
    if (sizeof (packet)<12) return {};
    if (!checker.check_source1(packet[0])) return {};
    if(!checker.check_message_type1(packet[1])) return {};
    uint8_t source =packet[0];
    uint8_t type = packet[1];
    packet.erase(packet.begin(),packet.begin()+2);
    uint8_t number[2] = {packet[0],packet[1]};
    packet.erase(packet.begin(),packet.begin()+2);
    std::vector<uint8_t> date;
    date.assign(packet.begin(),packet.begin()+20);
    packet.erase(packet.begin(),packet.begin()+20);
    std::vector<uint8_t> data;
    data.assign(packet.begin(), packet.end());
    auto result_packet = ProtSRJ_create(source, date);
    result_packet.number_message.assign(number[0], number[1]);
    result_packet.packet_message_type = type;
    result_packet.create_message_data(type);
    result_packet.message_data->add_data(data);
    return result_packet;
}
std::vector<uint8_t> ProtSRJ::ToPacket(){

    std::vector<uint8_t> packet;

    // Добавляем данные в вектор
    packet.push_back(packet_source); // packet_source
    packet.push_back(packet_message_type); // packet_message_type
    packet.insert(packet.end(), reinterpret_cast<const uint8_t*>(&number_message), reinterpret_cast<const uint8_t*>(&number_message) + sizeof(number_message)); // number_message
    packet.insert(packet.end(), reinterpret_cast<const uint8_t*>(&send_date_and_time), reinterpret_cast<const uint8_t*>(&send_date_and_time) + sizeof(send_date_and_time)); // send_date_and_time
    packet.insert(packet.end(), message_data->get_data().begin(), message_data->get_data().end()); // message_data

    // Возвращаем вектор с данными пакета
    return packet;
}
void ProtSRJ::create_message_data(uint8_t message_type){
    switch (message_type) {
    case INFORMATION_MESSAGE:
        message_data = new ZeroTypeMesage();
        break;
    case WARNING_MESSAGE:
        message_data = new FirstTypeMassage();
        break;
    case START_PROCESS_MESSAGE:
        message_data = new SecondTypeMessage();
        break;
    case PROCESS_FINISH_MESSAGE:
        message_data = new ThirdTypeMessage();
        break;
    case STOP_STATION_MESSAGE:
        message_data = new FourthTypeMessage();
        break;
    case START_STATION_MESSAGE:
        message_data = new FifthTypeMessage();
        break;
    default:
        throw std::runtime_error("Message type is invalid");
    }
}
void ProtSRJ::add_number_message(uint8_t num_message){
    std::string str_num = std::to_string(num_message);
    std::vector<uint8_t> number_message;
    qDebug()<< "num \n";
    number_message.clear();
    qDebug()<< "clear \n";
    number_message.resize(str_num.length());
    qDebug()<< "resize \n";
    for (int i=0;i<str_num.length();i++){
        number_message[i]=str_num[i];
    }
    qDebug()<< "done \n";
}
void ProtSRJ::add_data(uint8_t message_type, std::string data){
    if (!data.empty() && data.size()>480)
        throw std::runtime_error("Data is too much");
    packet_message_type = message_type;
    create_message_data(message_type);
    message_data->add_data(data);
}
std::vector<char> ProtSRJ::get_char_date(){
    std::vector<char> char_date ;
    for (int i=0;i<send_date_and_time.size();i++){
        char_date.push_back(char(send_date_and_time[i]));
    }
    return char_date;
}
