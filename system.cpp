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
void system::send_first_type_message(std::string msg){
    if (!senderThread)
        senderThread=new MessageSendThread();
    int i=0;
    senderThread->buffer[i]=source_code;
    i++;
    senderThread->buffer[i]=WARNING_MESSAGE;
    i++;
    senderThread->buffer[i]=std::to_string(id_message)[0];
    id_message++;
    i++;
    int j=0;
    ProtSRJ date_creator;
    std::vector<uint8_t> date=date_creator.create_date();
    for (int j=0;j<date.size();j++){
        senderThread->buffer[i]=date[j];
        i++;
    }

    for (int j=0;j<msg.size();j++){
        senderThread->buffer[i]=msg[j];
        i++;
    }
    senderThread->buffer[i]=0;
    qDebug()<<senderThread->buffer;
    senderThread->start();

}

void system::send_fifth_type_message(){
    if (!senderThread)
        senderThread=new MessageSendThread();
    int i=0;
    senderThread->buffer[i]=source_code;
    i++;
    senderThread->buffer[i]=START_STATION_MESSAGE;
    i++;
    senderThread->buffer[i]=std::to_string(id_message)[0];
    id_message++;
    i++;
    int j=0;
    ProtSRJ date_creator;
    std::vector<uint8_t> date=date_creator.create_date();
    for (int j=0;j<date.size();j++){
        senderThread->buffer[i]=date[j];
        i++;
    }

//    for (int j=0;j<msg.size();j++){
//        senderThread->buffer[i]=msg[j];
//        i++;
//    }
    senderThread->buffer[i]=0;
    qDebug()<<senderThread->buffer;
    senderThread->start();
}
void system::send_second_type_message(std::string msg){
    if (!senderThread)
        senderThread=new MessageSendThread();
    int i=0;
    senderThread->buffer[i]=source_code;
    i++;
    senderThread->buffer[i]=START_PROCESS_MESSAGE;
    i++;
    senderThread->buffer[i]=std::to_string(id_message)[0];
    id_message++;
    i++;
    int j=0;
    ProtSRJ date_creator;
    std::vector<uint8_t> date=date_creator.create_date();
    for (int j=0;j<date.size();j++){
        senderThread->buffer[i]=date[j];
        i++;
    }

    for (int j=0;j<msg.size();j++){
        senderThread->buffer[i]=msg[j];
        i++;
    }
    senderThread->buffer[i]=0;
    qDebug()<<senderThread->buffer;
    senderThread->start();
}
void system::send_third_type_message(std::string msg){
    if (!senderThread)
        senderThread=new MessageSendThread();
    int i=0;
    senderThread->buffer[i]=source_code;
    i++;
    senderThread->buffer[i]=PROCESS_FINISH_MESSAGE;
    i++;
    senderThread->buffer[i]=std::to_string(id_message)[0];
    id_message++;
    i++;
    int j=0;
    ProtSRJ date_creator;
    std::vector<uint8_t> date=date_creator.create_date();
    for (int j=0;j<date.size();j++){
        senderThread->buffer[i]=date[j];
        i++;
    }

    for (int j=0;j<msg.size();j++){
        senderThread->buffer[i]=msg[j];
        i++;
    }
    senderThread->buffer[i]=0;
    qDebug()<<senderThread->buffer;
    senderThread->start();
}
void system::send_fourth_type_message(){
    if (!senderThread)
        senderThread=new MessageSendThread();
    int i=0;
    senderThread->buffer[i]=source_code;
    i++;
    senderThread->buffer[i]=STOP_STATION_MESSAGE;
    i++;
    senderThread->buffer[i]=std::to_string(id_message)[0];
    id_message++;
    i++;
    int j=0;
    ProtSRJ date_creator;
    std::vector<uint8_t> date=date_creator.create_date();
    for (int j=0;j<date.size();j++){
        senderThread->buffer[i]=date[j];
        i++;
    }

//    for (int j=0;j<msg.size();j++){
//        senderThread->buffer[i]=msg[j];
//        i++;
//    }
    senderThread->buffer[i]=0;
    qDebug()<<senderThread->buffer;
    senderThread->start();
}
system::system(uint8_t source_code,std::string log){
    this->source_code=source_code;
    this->log=log;
    //происходит отправка 5 типа сообщения и начинается прием сообщений
    qDebug() << contructor_message;
    //у разных классов будут раззный сообщения
}


system::~system() {
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
std::string system::recieve(){
    if (!receiverThread) {
        receiverThread = new MessageReceiverThread();
    }
    ProtSRJ packet;
    std::string msg, res=" получила сообщение от ";
    bool receiving=true;
    while (receiving) {
        if (!receiverThread->isRunning())
            receiverThread->start();
        msg=receiverThread->message;
        if (source_code==msg[0])
            continue;
        else {
            std::string systemName;
            switch (source_code) {
            case APCS:
                res="АСУ ТП"+res;
                break;
            case SCS:
                res="СКС"+res;
                break;
            case SYSTEM_MEASUREMENT_MOVEMENT:
                res="АСУ ТП"+res;
                break;
            case SYSTEM_OF_STABILIZATION:
                res="Система стабилизации"+res;
                break;
            case LBORDER_SYSTEM_TENZOMETRIA:
                res="Левая система тензометрии"+res;
                break;
            case RBORDER_SYSTEM_TENZOMETRIA:
                res="Правая система стабилизации"+res;
                break;
            case LBORDER_SUBSYSTEM_DIST_VIS_WATCH:
                res="Левая подсистема дистанционного наблюдения"+res;
                break;
            case RBORDER_SUBSYSTEM_DIST_VIS_WATCH:
                res="Правая подсистема дистанционного наблюдения"+res;
                break;
            case LBORDER_SUBSYSTEM_REGISTER_CRACK:
                res="Левая подсистема регистрации трещин"+res;
                break;
            case RBORDER_SUBSYSTEM_REGISTER_CRACK:
                res="Правая подсистема регистрации трещин"+res;
                break;
            case LBORDER_ACUSTIC_SYSTEM:
                res="Левая акустическая система"+res;
                break;
            case RBORDER_ACUSTIC_SYSTEM:
                res="Правая акустическая система"+res;
                break;
            }
        }
    }

    return senderThread->message;
}


