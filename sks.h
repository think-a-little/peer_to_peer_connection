#ifndef SKS_H
#define SKS_H

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

class MessageReceiverThreadSKS;
class MessageSendThreadSKS;

namespace Ui {
class sks;
}

class sks : public QMainWindow
{
    Q_OBJECT

public:
    explicit sks(QWidget *parent = nullptr);
    ~sks();

    void finish();

private slots:

    void handleMessageReceived(const QString& message);

    void handleMessageSend();

    void on_firstTypeMsgBut_clicked();

    void on_secondTypeMsgBut_clicked();

private:
    Ui::sks *ui;
    int sock;
    sockaddr_in addr;
    char buffer[1024];

    std::mutex mtx;
    std::condition_variable cv;
    bool receiveDo = false;

    MessageReceiverThreadSKS* receiverThread=nullptr;
    MessageSendThreadSKS* senderThread=nullptr;
};


class MessageReceiverThreadSKS : public QThread
{
    Q_OBJECT

public:
    explicit MessageReceiverThreadSKS(QObject *parent = nullptr);

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


class MessageSendThreadSKS : public QThread
{
    Q_OBJECT

public:
    explicit MessageSendThreadSKS(QObject *parent = nullptr);
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

#endif // SKS_H
