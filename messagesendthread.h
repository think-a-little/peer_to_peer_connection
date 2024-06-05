#ifndef MESSAGESENDTHREAD_H
#define MESSAGESENDTHREAD_H


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
#include <string>
#include <unordered_map>
#define BROADCAST_ADDRESS "192.168.235.255"
#define BROADCAST_PORT 21000

class MessageSendThread : public QThread
{
    Q_OBJECT

public:
    explicit MessageSendThread(QObject *parent = nullptr);
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


#endif // MESSAGESENDTHREAD_H
