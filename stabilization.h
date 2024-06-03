#ifndef STABILIZATION_H
#define STABILIZATION_H
#include <QThread>
#include <QMainWindow>

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

namespace Ui {
class stabilization;
}
class MessageSendThreadStab;
class MessageReceiverThreadStab;
class stabilization : public QMainWindow
{
    Q_OBJECT

public:
    char buffer[1024];
    explicit stabilization(QWidget *parent = nullptr);
    ~stabilization();
    MessageReceiverThreadStab* receiverThread=nullptr;
    MessageSendThreadStab* senderThread=nullptr;

private slots:
    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::stabilization *ui;
private slots:
    void handleMessageReceived(const QString& message);

    void handleMessageSend();
};
class MessageReceiverThreadStab : public QThread
{
    Q_OBJECT

public:
    explicit MessageReceiverThreadStab(QObject *parent = nullptr);

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


class MessageSendThreadStab : public QThread
{
    Q_OBJECT

public:
    explicit MessageSendThreadStab(QObject *parent = nullptr);
    char buffer[1024];
    std::string message;

    void handleMessageReceived(const QString& message);

    void handleMessageSend();
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

#endif // STABILIZATION_H
