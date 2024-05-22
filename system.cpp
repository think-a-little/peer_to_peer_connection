#include "system.h"

system::system() {
    connect();

//        std::string data=std::to_string(flight_type)+std::to_string(flight_number)+
//                std::to_string(cycle_number)+std::to_string(segment_number);
//        send(data);
}

void system::connect() {
    sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock != 0) {
            std::cerr << "Ошибка создания сокета" << std::endl;
            exit(EXIT_FAILURE);
        }
            addr.sin_family = AF_INET; // IPv4
            addr.sin_port = htons(port); // Порт
            addr.sin_addr.s_addr = INADDR_ANY; // Принимаемые все IP адреса
            bind(sock, (struct sockaddr*)&addr, sizeof(addr));
}

//void Model::receive() {
//    socklen_t addr_size = sizeof(addr);
//    recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_size);
//}

//void Model::send(std::string message) {
//    sendto(sock, message.c_str(), message.size(), 0, (struct sockaddr*)&addr, sizeof(addr));
//}

void system::finish() {
    if(sock == 0) close(sock);
}

system::~system() {
    finish();
}
