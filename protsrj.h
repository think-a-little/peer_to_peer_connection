#ifndef PROTSRJ_H
#define PROTSRJ_H
#include <cstdint>
#include "protsrjdata.h"
#include <vector>
#include <sstream>
class ProtSRJ
{
public:
   uint8_t packet_source, packet_message_type;
   std::vector<uint8_t> number_message;
   std::vector<uint8_t> send_date_and_time;
   ProtSRJData *message_data;
   ProtSRJ ProtSRJ_create(uint8_t source);
   ProtSRJ ProtSRJ_create(uint8_t source, std::vector<uint8_t> date_and_time);
   ProtSRJ parse_packet(std::vector<uint8_t> packet);
   std::vector<uint8_t> ToPacket();
   void add_number_message(short num_message);
   void add_data(uint8_t message_type, std::vector<char> data);
   std::vector<char> get_char_date();
   void create_message_data(uint8_t message_type);
   std::vector<uint8_t> create_date();
private:


};

#endif // PROTSRJ_H
