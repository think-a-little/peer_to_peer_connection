#include "system.h"
#include <vector>
#include <qdebug.h>
#include "srj_consts.h"
system::system() {
    if (!senderThread)
        senderThread=new MessageSendThread();
    senderThread->start();
}
void system::send_zero_type_message(){
    send_message(" ",INFORMATION_MESSAGE);
}
void system::send_message(std::string msg, uint8_t type){
    int i=0;
    senderThread->buffer[i]=source_code;
    i++;
    senderThread->buffer[i]=type;
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
    if (msg!=" "){
        for (int j=0;j<msg.size();j++){
            senderThread->buffer[i]=msg[j];
            i++;
        }
    }
    senderThread->buffer[i]=0;
}
void system::send_first_type_message(std::string msg){
        send_message(msg,WARNING_MESSAGE);
}

void system::send_fifth_type_message(){

    std::string msg=" ";
    qDebug()<<"5 type";
    send_message(msg,START_PROCESS_MESSAGE);
}
void system::send_second_type_message(std::string msg){
    send_message(msg, START_PROCESS_MESSAGE);
}
void system::send_third_type_message(std::string msg){
    send_message(msg, PROCESS_FINISH_MESSAGE);
}
void system::send_fourth_type_message(){
    std::string msg=" ";
    send_message(msg,STOP_STATION_MESSAGE);
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
void system::sleep(int timer){
    int stime = time(NULL);
    while (true) {
        if (time(NULL) - stime == timer) break;
    }
}
QString system::recieve(QString msg){
    if (source_code == msg[0])
        return "  ";
    ProtSRJ packet;
    QString res=" от ";
    bool receiving=true;
    QString systemName;
    std::unordered_map<uint8_t,QString> codesOfSystems = {{APCS, "АСУ ТП"}, {SCS, "СКС"},
                                                          {SYSTEM_MEASUREMENT_MOVEMENT, "Система измерения перемещения"},
                                                          {SYSTEM_OF_STABILIZATION,"Система стабилизации"}, {LBORDER_SYSTEM_TENZOMETRIA, "Левая система тензометрии"},
                                                          {RBORDER_SYSTEM_TENZOMETRIA,"Правая система тензометрии"},{LBORDER_SUBSYSTEM_DIST_VIS_WATCH,"Левая подсистема дистанционного наблюдения"},
                                                          {RBORDER_SUBSYSTEM_DIST_VIS_WATCH,"Правая подсистема дистанционного наблюдения"},
                                                          {LBORDER_SUBSYSTEM_REGISTER_CRACK,"Левая подсистема регистрации трещин"},
                                                          {RBORDER_SUBSYSTEM_REGISTER_CRACK,"Правая подсистема регистрации трещин"},{LBORDER_ACUSTIC_SYSTEM,"Левая акустическая система"},
                                                          {RBORDER_ACUSTIC_SYSTEM,"Правая акустическая система"}},
            codesOfMessages= {{INFORMATION_MESSAGE,"информациионное сообщение"},{WARNING_MESSAGE,"предупреждение"},
                              {START_PROCESS_MESSAGE,"Сообщение о старте системы"},{PROCESS_FINISH_MESSAGE,"Подтверждение о получении сообщения"},
                              {STOP_STATION_MESSAGE,"Сообщение о остановки станции"},
                              {START_STATION_MESSAGE,"Сообщение о запуске станции"}};
    for (const auto& pair:codesOfSystems){
        if (source_code == pair.first)
            res=pair.second+res;
        if (msg[0] == pair.first)
            res=res+pair.second;

    }
    res=res+" получила ";
    for (const auto& pair:codesOfMessages){
        if (msg[1]==pair.first)
            res=res+pair.second;
    }
    res = res + " в ";
    for (int i=3;i<23;i++)
        res=res+msg[i];
    
    QString answer;
    for (int i=23;i<msg.size();i++)
        answer=answer+msg[i];
    return res;
}


