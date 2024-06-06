#ifndef SYSTEM_H
#define SYSTEM_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <QDebug>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "protsrj.h"
#include <string>
#include <unordered_map>
#include "messagesendthread.h"
#include "srj_consts.h"
class system
{
public:
    void sleep(int timer);

    uint8_t source_code;
    bool is_recive=true;
    short id_message=1;
    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;
    std::string log;
    struct sent_message{
        ProtSRJ packet;
    };
    void send_message(std::string msg, uint8_t type);
    QString contructor_message = "Система начала работу" ;
    void write_log(std::string text);
    void stop_working();
    std::vector<sent_message>stack_sent_messages;
    virtual void save_data(ProtSRJ packet, int id_save);
    void parsing_packet(ProtSRJ packet);
    void parse_zero_type_message(ProtSRJ packet);
    void parse_first_type_message(ProtSRJ packet);
    void parse_second_type_message(ProtSRJ packet);
    void parse_third_type_message(ProtSRJ packet);
    void parse_fourth_type_message(ProtSRJ packet);
    void parse_fifth_type_message(ProtSRJ packet);
public:
    system();
    ~system();
    MessageSendThread* senderThread = nullptr;
    MessageReceiverThread* receiverThread=nullptr;
    system(uint8_t source_code,std::string log);
    virtual void send_zero_type_message();
    virtual void send_first_type_message(std::string data);
    virtual void send_second_type_message(std::string msg);
    virtual void send_third_type_message(std::string msg);
    virtual void send_fourth_type_message();
    virtual void send_fifth_type_message();
    QString recieve(QString msg);
};

#endif // MODEL_H
