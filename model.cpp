#include "model.h"

Model::Model(std::string who, int flight_type, int flight_number, int cycle_number,
             int segment_number) {
    connect(who);
    if(who=="server") {

    }
    else if(who=="client") {
//        this->flight_type=flight_type;
//        this->flight_number=flight_number;
//        this->cycle_number=cycle_number;
//        this->segment_number=segment_number;
        std::string data=std::to_string(flight_type)+std::to_string(flight_number)+
                std::to_string(cycle_number)+std::to_string(segment_number);
        send(data);
    }
    else;
}

void Model::connect(std::string who) {
    sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock != 0) {
            std::cerr << "Ошибка создания сокета" << std::endl;
            exit(EXIT_FAILURE);
        }
            addr.sin_family = AF_INET; // IPv4
            addr.sin_port = htons(port); // Порт сервера
            if(who=="server") {
                addr.sin_addr.s_addr = INADDR_ANY; // Принимаемые все IP адреса
                bind(sock, (struct sockaddr*)&addr, sizeof(addr));
            }
            else if(who=="client") {
                inet_pton(AF_INET, "127.0.0.1", &(addr.sin_addr)); // IP сервера
            }
            else;
}

void Model::receive() {
    socklen_t addr_size = sizeof(addr);
    recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_size);
}

void Model::send(std::string message) {
    sendto(sock, message.c_str(), message.size(), 0, (struct sockaddr*)&addr, sizeof(addr));
}

void Model::finish() {
    close(sock);
}

