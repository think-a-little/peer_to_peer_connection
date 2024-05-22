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
protected:
    const int port=12000;
    int sock;
    sockaddr_in addr;
    char buffer[1024];
public:
    Model(std::string who, int flight_type, int flight_number, int cycle_number, int segment_number);
    void connect(std::string who);
    void receive();
    void send(std::string message);
    void finish();
};

#endif // MODEL_H
