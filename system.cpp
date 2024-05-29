#include "system.h"
#include <vector>
#include <qdebug.h>
#include "srj_consts.h"


void MessageReceiverThread::run()
{
    qDebug()<<"HELLO";
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        exit(EXIT_FAILURE);
    }

    int broadcastPermission = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastPermission, sizeof(broadcastPermission)) < 0) {
        std::cerr << "Ошибка установки опции SO_BROADCAST" << std::endl;
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(BROADCAST_PORT);

    if (bind(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Ошибка привязки сокета" << std::endl;
        exit(EXIT_FAILURE);
    }

    socklen_t clientAddrLength = sizeof(clientAddr);
    ssize_t receivedBytes = 0;

    while(true) {
        receivedBytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrLength);
        if (receivedBytes > 0) {
            emit messageReceived(QString::fromUtf8(buffer));
            for (int i = 0; i < 1024; i++)
                buffer[i] = ' ';
            break;
        }
}

    ::close(sock);
}


void system::handleMessageReceived(const QString& message)
{
//    ui->textEdit->insertPlainText(message);
}





MessageSendThread::MessageSendThread(QObject *parent)
    : QThread(parent)
{
}

void MessageSendThread::run()
{
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        exit(EXIT_FAILURE);
    }

    int broadcastPermission = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastPermission, sizeof(broadcastPermission)) < 0) {
        std::cerr << "Ошибка установки опции SO_BROADCAST" << std::endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in broadcastAddr;
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));
    broadcastAddr.sin_family = AF_INET;
    broadcastAddr.sin_addr.s_addr = inet_addr(BROADCAST_ADDRESS);
    broadcastAddr.sin_port = htons(BROADCAST_PORT);


    std::string message = "Hello";
    emit messageSend();
    while(true) {
    sleep(1);
    if (sendto(sock, message.c_str(), message.size(), 0, (struct sockaddr*)&broadcastAddr, sizeof(broadcastAddr))!= message.size()) {
        std::cerr << "Ошибка отправки сообщения" << std::endl;
        exit(EXIT_FAILURE);
    }
    }

    ::close(sock);
}


void system::handleMessageSend()
{
//    QByteArray ba = ui->textEdit->toPlainText().toLatin1();
//    char* ch = ba.data();
//    for(int i=0; i<1024; i++) buffer[i]=ch[i];
}


system::system(QObject *parent) :
    QObject(parent)
{
    connecting();
}

void system::send_zero_type_message(){
    qDebug()<<"0 type msg /n";
}
void system::send_fifth_type_message(){
    qDebug()<<"0 type msg /n";
}
void system::send_second_type_message(std::vector<char> data){
    qDebug()<<"0 type msg /n";
}
void system::send_third_type_message(std::vector<char> data){
    qDebug()<<"0 type msg /n";
}
void system::send_fourth_type_message(){
    qDebug()<<"0 type msg /n";
}
void system::send_first_type_message(std::vector<char> data){
    qDebug()<<"0 type msg /n";
}
system::system(uint8_t source_code,std::string log){
    this->source_code=source_code;
    this->log=log;
    //происходит отправка 5 типа сообщения и начинается прием сообщений
    qDebug() << contructor_message;
    //у разных классов будут раззный сообщения
}

void system::connecting() {
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        exit(EXIT_FAILURE);
    }

    int broadcastPermission = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastPermission, sizeof(broadcastPermission)) < 0) {
        std::cerr << "Ошибка установки опции SO_BROADCAST" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void system::finish() {
    if(sock == 0) close(sock);
}

void system::button_clicked_send() {
    if (!senderThread) {
            senderThread = new MessageSendThread();
            connect(senderThread, &MessageSendThread::messageSend, this, &system::handleMessageSend);
    }
            senderThread->start();
}

void system::button_clicked_receive() {
    if (!receiverThread) {
            receiverThread = new MessageReceiverThread();
            connect(receiverThread, &MessageReceiverThread::messageReceived, this, &system::handleMessageReceived);
    }
            receiverThread->start();

}

system::~system() {
    finish();
}

void system::write_log(std::string text){
    if (log.length()>0)
        log+=text;
}
void system::stop_working(){
    is_recive=false;
    for (int i=0;i<stack_sent_messages.size();i++){
        //здесь должен останавливатьса таймер от stack_sent_messages[i]
    }
}

void system::save_data(ProtSRJ packet, int id_save){
    if (id_save==1){
        sent_message sm;
        sm.packet=packet;
        //установка таймера в sm
        stack_sent_messages.push_back(sm);
    }
}
void system::parsing_packet(ProtSRJ packet){
    switch (packet.packet_message_type) {
    case INFORMATION_MESSAGE:
        parse_zero_type_message(packet);
        break;
    case WARNING_MESSAGE:
        parse_first_type_message(packet);
        break;
    case START_PROCESS_MESSAGE:
        parse_second_type_message(packet);
        break;
    case PROCESS_FINISH_MESSAGE:
        parse_third_type_message(packet);
        break;
    case STOP_STATION_MESSAGE:
        parse_fourth_type_message(packet);
        break;
    case START_STATION_MESSAGE:
        parse_fifth_type_message(packet);
        break;
    }
}
void system::parse_zero_type_message(ProtSRJ packet){
    write_log("Система получила сообщение типа 0");
    if (packet.packet_source==APCS && packet.message_data->parse_data().size()>0)
        write_log("Системный таймер синхронизирован");

}
void system::parse_first_type_message(ProtSRJ packet){
    write_log("Система получила сообщение типа 1");
    std::vector<char> data_for_third_message = {char(packet.packet_source),
    char(packet.number_message[0]),char(packet.number_message[1])};
    //Отправка сообщения третьего типа

}
void system::parse_second_type_message(ProtSRJ packet){
    write_log("Система получила сообщение типа 2");
    std::vector<uint8_t> data_source;
    data_source.assign(packet.message_data->get_data().begin(),packet.message_data->get_data().end());
    for (int i=0;i<data_source.size();i++)
        if (data_source[i]==source_code){
            std::vector<char> data_for_third_message={char(packet.packet_source),
            char(packet.number_message[0]),char(packet.number_message[1])};
            //Отправка сообщения 3 типа
            break;
        }

}
void system::parse_third_type_message(ProtSRJ packet){
    std::vector<uint8_t> data_number_message = {packet.message_data->get_data()[1],
    packet.message_data->get_data()[2]};
    for (int i=0;i<stack_sent_messages.size();i++){
        if (data_number_message[0]== stack_sent_messages[i].packet.number_message[0]
                && data_number_message[1]==stack_sent_messages[i].packet.number_message[1])
        {
            //установка таймера у итого элемента
            write_log("Система получила подверждение для сообщения типа 1");
            stack_sent_messages.erase(stack_sent_messages.begin()+i);
            return;
        }

    }
}
void system::parse_fourth_type_message(ProtSRJ packet){
    write_log("Система с кодом"+std::to_string(packet.packet_source)+" прекратила работать");
}
void system::parse_fifth_type_message(ProtSRJ packet){
    return;//она только у асу тп че то делает
}



