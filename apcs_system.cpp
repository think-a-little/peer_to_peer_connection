#include "apcs_system.h"

apcs_system::apcs_system(int flight_type, int flight_number, int cycle_number, int segment_number) : system(),
    flight_type(flight_type),
    flight_number(flight_number),
    cycle_number(cycle_number),
segment_number(segment_number) {
    auto lambda_receive = [this]() {
                receive();
            };
    auto lambda_send = [this](std::string message) {
                send(message);
            };
    std::thread receiverThread(lambda_receive);
    std::thread senderThread(lambda_send, "message");

    receiverThread.join();
    senderThread.join();
}

void apcs_system::receive() {
   if(reciveDo){
//    std::this_thread::sleep_for(std::chrono::seconds(1)); // Имитация задержки
//    char buffer[1024];
//    socklen_t addr_size = sizeof(addr);
//    recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_size);
//    std::cout << "Ответ сервера: " << buffer << std::endl;

//    setReady(true);
    qDebug()<<"АСУ ТП начала работу" <<flight_type;
    reciveDo=false;
   }
}
void apcs_system::send(std::string message) {
    message = "Hello, Server!";
    sendto(sock, message.c_str(), message.size(), 0, (struct sockaddr*)&addr, sizeof(addr));
}
