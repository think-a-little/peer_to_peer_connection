#include "apcs.h"

void APCS::receive() {
    waiting();
}

void APCS::send(std::string message) {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Имитация задержки
    setReady(true);
}
