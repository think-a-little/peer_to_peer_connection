#include "system.h"

system::system() {
 //   connect();
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

void system::finish() {
    if(sock == 0) close(sock);
}

void system::setReady(bool status) {
    std::lock_guard<std::mutex> lock(mtx);
    ready = status;
    cv.notify_all();
}

bool system::isReady() {
    std::lock_guard<std::mutex> lock(mtx);
    return ready;
}

void system::waiting() {
    std::unique_lock<std::mutex> lock(mtx); // Создаем unique_lock, который автоматически блокирует мьютекс
    cv.wait(lock, [this]{return isReady();}); // Используем unique_lock в качестве аргумента для cv.wait()
}

system::~system() {
    finish();
}
