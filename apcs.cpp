#include "apcs.h"
#include "ui_apcs.h"
#include <regex>
apcs::apcs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::apcs)
{
    ui->setupUi(this);
}

APCS::APCS(int flight_type, int flight_number, int cycle_number, int segment_number) : system(),
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

void APCS::receive() {
   if(reciveDo){
//    std::this_thread::sleep_for(std::chrono::seconds(1)); // Имитация задержки
//    char buffer[1024];
//    socklen_t addr_size = sizeof(addr);
//    recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_size);
//    std::cout << "Ответ сервера: " << buffer << std::endl;

//    setReady(true);
    qDebug()<<"АСУ ТП начала работу";
    reciveDo=false;
   }
}

void APCS::send(std::string message) {
    message = "Hello, Server!";
    sendto(sock, message.c_str(), message.size(), 0, (struct sockaddr*)&addr, sizeof(addr));
}

apcs::~apcs()
{
    delete ui;
}

void apcs::on_firstTypeMesageBut_clicked()
{
    std::regex pattern("[0-6]{1,480}");
    if (!(std::regex_match(ui->firstTypeMsgText->toPlainText().toStdString(),pattern))){
        ui->firstTypeMsgText->setText("Ошибка");
        return;
    }
}

void apcs::on_secondTypeMesageBut_clicked()
{
    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
        ui->secondTypeMsgText->setText("Ошибка");
        return;
    }

}
