#include "crack.h"
#include "ui_crack.h"
#include <regex>
crack::crack(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::crack)
{
    ui->setupUi(this);
}

crack::~crack()
{
    delete ui;
}

void crack::on_firstTypeMesageBut_clicked()
{
    std::regex pattern("[0-6]{1,480}");
    if (!(std::regex_match(ui->firstTypeMsgText->toPlainText().toStdString(),pattern))){
        ui->firstTypeMsgText->setText("Ошибка");
        return;
    }
    if (!senderThread) {
        senderThread = new MessageSendThreadCrack(this);
        connect(senderThread, &MessageSendThreadCrack::messageSend, this, &crack::handleMessageSend);
    }
    senderThread->message =" crack 1 " + ui->firstTypeMsgText->toPlainText().toStdString();
    senderThread->start();
}

void crack::on_secondTypeMesageBut_clicked()
{
    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
        ui->secondTypeMsgText->setText("Ошибка");
        return;
    }
}


void crack::finish() {
    if(sock == 0) ::close(sock);
}

MessageReceiverThreadCrack::MessageReceiverThreadCrack(QObject *parent)
    : QThread(parent)
{
}

void MessageReceiverThreadCrack::run()
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

    while (bind(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Ошибка привязки сокета" << std::endl;
        //        exit(EXIT_FAILURE);
    }

    socklen_t clientAddrLength = sizeof(clientAddr);
    ssize_t receivedBytes = 0;

    receivedBytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrLength);
    if (receivedBytes > 0) {
        buffer[receivedBytes]=0;
        emit messageReceived(QString::fromUtf8(buffer));

    }

    ::close(sock);
}
void crack::handleMessageReceived(const QString& message)
{
    ui->textEdit_3->insertPlainText(message);
}

MessageSendThreadCrack::MessageSendThreadCrack(QObject *parent)
    : QThread(parent)
{
}

void MessageSendThreadCrack::run()
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


    emit messageSend();
    if (sendto(sock, message.c_str(), message.size(), 0, (struct sockaddr*)&broadcastAddr, sizeof(broadcastAddr))!= message.size()) {
        std::cerr << "Ошибка отправки сообщения" << std::endl;
        exit(EXIT_FAILURE);
    }

    ::close(sock);
}


void crack::handleMessageSend()
{
    QByteArray ba = ui->firstTypeMsgText->toPlainText().toLatin1();
    char* ch = ba.data();
    for(int i=0; i<1024; i++) buffer[i]=ch[i];
}
