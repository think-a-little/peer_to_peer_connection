#include "apcs.h"

APCS::APCS(int flight_type, int flight_number, int cycle_number, int segment_number) : Model("client", flight_type, flight_number, cycle_number, segment_number) {
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (client_fd != 0) {
            std::cerr << "Ошибка создания сокета" << std::endl;
            exit(EXIT_FAILURE);
        }
        sockaddr_in client_addr;
            client_addr.sin_family = AF_INET; // IPv4
            client_addr.sin_port = htons(port); // Порт сервера
            inet_pton(AF_INET, "127.0.0.1", &(client_addr.sin_addr)); // IP сервера

            std::string message = "Hello, Server!";
            sendto(client_fd, message.c_str(), message.size(), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));

            char buffer[1024];
            socklen_t addr_size = sizeof(client_addr);

            recvfrom(client_fd, buffer, 1024, 0, (struct sockaddr*)&client_addr, &addr_size);
            std::cout << "Ответ сервера: " << buffer << std::endl;

            close(client_fd);
}
