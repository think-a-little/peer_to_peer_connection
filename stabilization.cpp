#include "stabilization.h"
#include "ui_stabilization.h"
#include <regex>
stabilization::stabilization(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::stabilization)
{
    ui->setupUi(this);
    if (!receiverThread) {
        receiverThread = new MessageReceiverThread(this);
        connect(receiverThread, &MessageReceiverThread::messageReceived, this, &stabilization::updateTextEditSlot);
    }
    receiverThread->start();
}

stabilization::~stabilization()
{
    delete ui;
    finish();
}

void stabilization::updateTextEditSlot(const QString& text){
    ui->textEdit_3->setText(stab_sys->recieve( text));
}

void stabilization::on_firstTypeMesageBut_clicked()
{
    std::regex pattern("[0-6]{1,480}");
    if (!(std::regex_match(ui->firstTypeMsgText->toPlainText().toStdString(),pattern))){
        ui->firstTypeMsgText->setText("Ошибка");
        return;
    }
    if (!senderThread) {
        senderThread = new MessageSendThread(this);
    }
    std::string msg = ui->firstTypeMsgText->toPlainText().toStdString();
    stab_sys->send_first_type_message(msg);
}

void stabilization::on_secondTypeMesageBut_clicked()
{
    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
        ui->secondTypeMsgText->setText("Ошибка");
        return;
    }
}

void stabilization::finish() {
    if(sock == 0) ::close(sock);
}
