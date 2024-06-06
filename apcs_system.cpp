#include "apcs_system.h"

apcs_system::apcs_system(int flight_type, int flight_number, int cycle_number, int segment_number) :
    flight_type(flight_type),
    flight_number(flight_number),
    cycle_number(cycle_number),
segment_number(segment_number) {
    source_code=APCS;
    send_fifth_type_message();
}
QString apcs_system::recieve(QString msg){
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
    if (msg[1]==START_STATION_MESSAGE){
        std::string msg="";
        msg=msg+std::to_string(flight_type);
        msg=msg+std::to_string(flight_number);
        msg=msg+std::to_string(cycle_number);
        msg=msg+std::to_string(segment_number);
        send_zero_type_message(msg);
    }
    if (msg[1]==WARNING_MESSAGE || msg[1]==START_PROCESS_MESSAGE){
        std::string answer2="";
        answer2=answer2+char(msg.toStdString()[0]);
        answer2=answer2+char(msg.toStdString()[2]);
        send_third_type_message(answer2);}
    return res;
}
