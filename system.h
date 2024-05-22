#ifndef MODEL_H
#define MODEL_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

class system
{
protected:
    const int port=12000;
    int sock;
    sockaddr_in addr;
    char buffer[1024];
public:
    system();
    ~system();
    void connect();
    virtual void receive()=0;
    virtual void send(std::string message)=0;
    void finish();
};

#endif // MODEL_H
