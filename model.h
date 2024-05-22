#ifndef MODEL_H
#define MODEL_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

class Model
{
private:
    const int port=12000;
public:
    Model();
    virtual void get()=0;
    virtual void send()=0;

};

#endif // MODEL_H
