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
#include <QThread>
#include <mutex>
#include <condition_variable>
#include "protsrj.h"
#include <string>
#include <unordered_map>

#define BROADCAST_ADDRESS "255.255.255.255"
#define BROADCAST_PORT 21000

class MessageReceiverThread;
class MessageSendThread;

class system : public QObject
{
    Q_OBJECT
protected:
    const int port=21000;
    int sock;
    sockaddr_in addr;
    char buffer[1024];
    uint8_t source_code;
    bool is_recive=true;
    short id_message;
    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;
    std::string log;

    MessageReceiverThread* receiverThread=nullptr;
    MessageSendThread* senderThread=nullptr;

    struct sent_message{
        ProtSRJ packet;
    };
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

private slots:
    void button_clicked_send();

    void button_clicked_receive();

    void handleMessageReceived(const QString& message);

    void handleMessageSend();

public:
    explicit system(QObject *parent = nullptr);
    ~system();

    system(uint8_t source_code,std::string log);
    virtual void send_zero_type_message();
    virtual void send_first_type_message(std::vector<char> data);
    virtual void send_second_type_message(std::vector<char> data);
    virtual void send_third_type_message(std::vector<char> data);
    virtual void send_fifth_type_message();
    virtual void send_fourth_type_message();
    void connecting();
    virtual void receive()=0;
    virtual void send(std::string message)=0;
    void finish();
};

class MessageReceiverThread : public QThread
{
    Q_OBJECT

public:
    explicit MessageReceiverThread(QObject *parent = nullptr);

protected:
    void run() override;

signals:
    void messageReceived(const QString& message);

private:
    int sock;
    sockaddr_in serverAddr;
    sockaddr_in clientAddr;
    socklen_t clientAddrLength;
    char buffer[1024];
};


class MessageSendThread : public QThread
{
    Q_OBJECT

public:
    explicit MessageSendThread(QObject *parent = nullptr);

protected:
    void run() override;

signals:
    void messageSend();

private:
    int sock;
    sockaddr_in serverAddr;
    sockaddr_in clientAddr;
    socklen_t clientAddrLength;
    char buffer[1024];
};

#endif // MODEL_H
