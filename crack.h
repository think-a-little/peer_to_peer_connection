#ifndef CRACK_H
#define CRACK_H

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

#define BROADCAST_ADDRESS "255.255.255.255"
#define BROADCAST_PORT 37020

class MessageReceiverThreadCrack;
class MessageSendThreadCrack;

namespace Ui {
class crack;
}
class crack : public QMainWindow
{
    Q_OBJECT

public:
    explicit crack(QWidget *parent = nullptr);
    ~crack();

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
    Ui::crack *ui;
    const int port=37020;
    int sock;
    sockaddr_in addr;
    char buffer[1024];

    std::mutex mtx;
    std::condition_variable cv;
    bool receiveDo = false;

    MessageReceiverThreadCrack* receiverThread=nullptr;
    MessageSendThreadCrack* senderThread=nullptr;
};


class MessageReceiverThreadCrack : public QThread
{
    Q_OBJECT

public:
    explicit MessageReceiverThreadCrack(QObject *parent = nullptr);

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


class MessageSendThreadCrack : public QThread
{
    Q_OBJECT

public:
    explicit MessageSendThreadCrack(QObject *parent = nullptr);
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
#endif // CRACK_H
