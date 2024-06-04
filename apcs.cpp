#include "apcs.h"
#include "ui_apcs.h"
#include <regex>
#include "srj_consts.h"
apcs::apcs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::apcs)
{
    ui->setupUi(this);

}

apcs::~apcs()
{
    delete ui;
    finish();
}


void apcs::on_firstTypeMesageBut_clicked()
{
    std::regex pattern("[0-6]{1,480}");
    if (!(std::regex_match(ui->firstTypeMsgText->toPlainText().toStdString(),pattern))){
        ui->firstTypeMsgText->setText("Ошибка");
        return;
    }
    if (!senderThread) {
        senderThread = new MessageSendThread(this);

        //        connect(senderThread, &MessageSendThread::messageSend, this, &apcs::handleMessageSend);
    }
    int i=0;
    senderThread->buffer[i]=APCS;
    i++;
    senderThread->buffer[i]=WARNING_MESSAGE;
    i++;
    senderThread->buffer[i]=id_message;
    id_message++;
    i++;
    int j=0;

    std::string msg =ui->firstTypeMsgText->toPlainText().toStdString();
    while (j!=msg.size()) {
        senderThread->buffer[i]=msg[j];
        j++;
        i++;
    }
    j=0;
    ProtSRJ date_creator;
    std::vector<uint8_t> date=date_creator.create_date();
    while (j!=sizeof (date)){
        senderThread->buffer[i]=date[j];
        i++;
        j++;
    }
    senderThread->buffer[i]=0;
    senderThread->start();
    qDebug()<<senderThread->buffer;
}

void apcs::on_secondTypeMesageBut_clicked()
{
    //    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    //    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
    //        ui->secondTypeMsgText->setText("Ошибка");
    //        return;
    //    }
    if (!receiverThread) {
        receiverThread = new MessageReceiverThread(this);
        connect(receiverThread, &MessageReceiverThread::messageReceived, this, &apcs::handleMessageReceived);
    }
    receiverThread->start();

}
void apcs::finish() {
    if(sock == 0) ::close(sock);
}

MessageReceiverThread::MessageReceiverThread(QObject *parent)
    : QThread(parent)
{
}

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
        qDebug()<< buffer;
    }

    ::close(sock);
}
void apcs::handleMessageReceived(const QString& message)
{
    ui->textEdit_3->insertPlainText(message);
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


    emit messageSend();
    //    for (int i=0;i<sizeof (buffer);i++)
    message=buffer;
    qDebug()<<buffer<< ' '<< QString::fromStdString(message);
    if (sendto(sock, message.c_str(), message.size(), 0, (struct sockaddr*)&broadcastAddr, sizeof(broadcastAddr))!= message.size()) {
        std::cerr << "Ошибка отправки сообщения" << std::endl;
        exit(EXIT_FAILURE);
    }

    ::close(sock);
}


void apcs::handleMessageSend()
{
    QByteArray ba = ui->firstTypeMsgText->toPlainText().toLatin1();
    char* ch = ba.data();
    for(int i=0; i<1024; i++) buffer[i]=ch[i];
}

