#ifndef MODEL_H
#define MODEL_H

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

class system
{
protected:
    const int port=12000;
    int sock;
    sockaddr_in addr;
    char buffer[1024];

    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;
public:
    system();
    ~system();

    void connect();
    virtual void receive()=0;
    virtual void send(std::string message)=0;
    void finish();

    void setReady(bool status);
    bool isReady();
    void waiting();
};

#endif // MODEL_H
