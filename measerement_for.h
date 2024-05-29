#ifndef MEASEREMENT_FOR_H
#define MEASEREMENT_FOR_H

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

class MessageReceiverThreadMEAS;
class MessageSendThreadMEAS;

namespace Ui {
class measerement_for;
}

class measerement_for : public QMainWindow
{
    Q_OBJECT

public:
    explicit measerement_for(QWidget *parent = nullptr);
    ~measerement_for();

    void finish();

private slots:
    void handleMessageReceived(const QString& message);

    void handleMessageSend();

    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::measerement_for *ui;
    int sock;
    sockaddr_in addr;
    char buffer[1024];

    std::mutex mtx;
    std::condition_variable cv;
    bool receiveDo = false;

    MessageReceiverThreadMEAS* receiverThread=nullptr;
    MessageSendThreadMEAS* senderThread=nullptr;
};


class MessageReceiverThreadMEAS : public QThread
{
    Q_OBJECT

public:
    explicit MessageReceiverThreadMEAS(QObject *parent = nullptr);

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


class MessageSendThreadMEAS : public QThread
{
    Q_OBJECT

public:
    explicit MessageSendThreadMEAS(QObject *parent = nullptr);
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


#endif // MEASEREMENT_FOR_H
