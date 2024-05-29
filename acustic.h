#ifndef ACUSTIC_H
#define ACUSTIC_H


#include <QMainWindow>
#include <QThread>

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
#include "acustic_system.h"
#define BROADCAST_ADDRESS "255.255.255.255"
#define BROADCAST_PORT 37020

class MessageReceiverThreadAcustic;
class MessageSendThreadAcustic;

namespace Ui {
class acustic;
}
class acustic : public QMainWindow
{
    Q_OBJECT

public:
    explicit acustic(QWidget *parent = nullptr);
    ~acustic();
    acustic_system* acustic_sys;
    void con();

    void finish();

    void receive();

    void send(std::string message);

private slots:

    void handleMessageReceived(const QString& message);

    void handleMessageSend();

    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::acustic *ui;
    const int port=37020;
    int sock;
    sockaddr_in addr;
    char buffer[1024];

    std::mutex mtx;
    std::condition_variable cv;
    bool receiveDo = false;

    MessageReceiverThreadAcustic* receiverThread=nullptr;
    MessageSendThreadAcustic* senderThread=nullptr;
};


class MessageReceiverThreadAcustic : public QThread
{
    Q_OBJECT

public:
    explicit MessageReceiverThreadAcustic(QObject *parent = nullptr);

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


class MessageSendThreadAcustic : public QThread
{
    Q_OBJECT

public:
    explicit MessageSendThreadAcustic(QObject *parent = nullptr);
    char buffer[1024];
    std::string message;
protected:
    void run() override;

signals:
    void messageSend();

private:
    int sock;
    sockaddr_in serverAddr;
    sockaddr_in clientAddr;
    socklen_t clientAddrLength;

};

#endif // ACUSTIC_H
