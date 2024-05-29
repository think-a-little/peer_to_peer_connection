#ifndef DIST_SYSTEM_H
#define DIST_SYSTEM_H

#include <QWidget>
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

#include "system_dist.h"

#define BROADCAST_ADDRESS "255.255.255.255"
#define BROADCAST_PORT 37020

class MessageReceiverThreadDIST;
class MessageSendThreadDIST;

namespace Ui {
class dist_system;
}

class dist_system : public QWidget
{
    Q_OBJECT

public:
    explicit dist_system(QWidget *parent = nullptr);
    ~dist_system();

    void finish();

private slots:
    void handleMessageReceived(const QString& message);

    void handleMessageSend();

    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::dist_system *ui;
    system_dist* sd;
    const int port=37020;
    int sock;
    sockaddr_in addr;
    char buffer[1024];

    std::mutex mtx;
    std::condition_variable cv;
    bool receiveDo = false;

    MessageReceiverThreadDIST* receiverThread=nullptr;
    MessageSendThreadDIST* senderThread=nullptr;
};



class MessageReceiverThreadDIST : public QThread
{
    Q_OBJECT

public:
    explicit MessageReceiverThreadDIST(QObject *parent = nullptr);

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


class MessageSendThreadDIST : public QThread
{
    Q_OBJECT

public:
    explicit MessageSendThreadDIST(QObject *parent = nullptr);
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

#endif // DIST_SYSTEM_H
