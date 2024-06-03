#include "system.h"
#include <vector>
#include <qdebug.h>
#include "srj_consts.h"
system::system() {
    //   connect();
}
void system::send_zero_type_message(){
    qDebug()<<"0 type msg /n";
}
void system::send_fifth_type_message(){
    qDebug()<<"0 type msg /n";
}
void system::send_second_type_message(std::vector<char> data){
    qDebug()<<"0 type msg /n";
}
void system::send_third_type_message(std::vector<char> data){
    qDebug()<<"0 type msg /n";
}
void system::send_fourth_type_message(){
    qDebug()<<"0 type msg /n";
}
void system::send_first_type_message(std::vector<char> data){
    ProtSRJ packet, creator;
    packet = creator.ProtSRJ_create(source_code);
    packet.add_number_message(id_message);
    packet.add_data(WARNING_MESSAGE,data);


}
system::system(uint8_t source_code,std::string log){
    this->source_code=source_code;
    this->log=log;
    //происходит отправка 5 типа сообщения и начинается прием сообщений
    qDebug() << contructor_message;
    //у разных классов будут раззный сообщения
}

void system::connect() {
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock != 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        exit(EXIT_FAILURE);
    }
    addr.sin_family = AF_INET; // IPv4
    addr.sin_port = htons(port); // Порт
    addr.sin_addr.s_addr = INADDR_ANY; // Принимаемые все IP адреса
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
}

void system::finish() {
    if(sock == 0) close(sock);
}

void system::setReady(bool status) {
    std::lock_guard<std::mutex> lock(mtx);
    ready = status;
    cv.notify_all();
}

bool system::isReady() {
    std::lock_guard<std::mutex> lock(mtx);
    return ready;
}

void system::waiting() {
    std::unique_lock<std::mutex> lock(mtx); // Создаем unique_lock, который автоматически блокирует мьютекс
    cv.wait(lock, [this]{return isReady();}); // Используем unique_lock в качестве аргумента для cv.wait()
}

system::~system() {
    finish();
}
void system::write_log(std::string text){
    if (log.length()>0)
        log+=text;
}
void system::stop_working(){
    is_recive=false;
    for (int i=0;i<stack_sent_messages.size();i++){
        //здесь должен останавливатьса таймер от stack_sent_messages[i]
    }
}
void system::save_data(ProtSRJ packet, int id_save){
    if (id_save==1){
        sent_message sm;
        sm.packet=packet;
        //установка таймера в sm
        stack_sent_messages.push_back(sm);
    }
}
void system::parsing_packet(ProtSRJ packet){
    switch (packet.packet_message_type) {
    case INFORMATION_MESSAGE:
        parse_zero_type_message(packet);
        break;
    case WARNING_MESSAGE:
        parse_first_type_message(packet);
        break;
    case START_PROCESS_MESSAGE:
        parse_second_type_message(packet);
        break;
    case PROCESS_FINISH_MESSAGE:
        parse_third_type_message(packet);
        break;
    case STOP_STATION_MESSAGE:
        parse_fourth_type_message(packet);
        break;
    case START_STATION_MESSAGE:
        parse_fifth_type_message(packet);
        break;
    }
}
void system::parse_zero_type_message(ProtSRJ packet){
    write_log("Система получила сообщение типа 0");
    if (packet.packet_source==APCS && packet.message_data->parse_data().size()>0)
        write_log("Системный таймер синхронизирован");

}
void system::parse_first_type_message(ProtSRJ packet){
    write_log("Система получила сообщение типа 1");
    std::vector<char> data_for_third_message = {char(packet.packet_source),
    char(packet.number_message[0]),char(packet.number_message[1])};
    //Отправка сообщения третьего типа

}
void system::parse_second_type_message(ProtSRJ packet){
    write_log("Система получила сообщение типа 2");
    std::vector<uint8_t> data_source;
    data_source.assign(packet.message_data->get_data().begin(),packet.message_data->get_data().end());
    for (int i=0;i<data_source.size();i++)
        if (data_source[i]==source_code){
            std::vector<char> data_for_third_message={char(packet.packet_source),
            char(packet.number_message[0]),char(packet.number_message[1])};
            //Отправка сообщения 3 типа
            break;
        }

}
void system::parse_third_type_message(ProtSRJ packet){
    std::vector<uint8_t> data_number_message = {packet.message_data->get_data()[1],
    packet.message_data->get_data()[2]};
    for (int i=0;i<stack_sent_messages.size();i++){
        if (data_number_message[0]== stack_sent_messages[i].packet.number_message[0]
                && data_number_message[1]==stack_sent_messages[i].packet.number_message[1])
        {
            //установка таймера у итого элемента
            write_log("Система получила подверждение для сообщения типа 1");
            stack_sent_messages.erase(stack_sent_messages.begin()+i);
            return;
        }

    }
}
void system::parse_fourth_type_message(ProtSRJ packet){
    write_log("Система с кодом"+std::to_string(packet.packet_source)+" прекратила работать");
}
void system::parse_fifth_type_message(ProtSRJ packet){
    return;//она только у асу тп че то делает
}



