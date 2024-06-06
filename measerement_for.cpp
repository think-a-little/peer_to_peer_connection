#include "measerement_for.h"
#include "ui_measerement_for.h"
#include <regex>
measerement_for::measerement_for(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::measerement_for)
{
    ui->setupUi(this);
    if (!receiverThread) {
        receiverThread = new MessageReceiverThread(this);
        connect(receiverThread, &MessageReceiverThread::messageReceived, this, &measerement_for::updateTextEditSlot);
    }
    receiverThread->start();
}

measerement_for::~measerement_for()
{
    delete ui;
    finish();
}

void measerement_for::updateTextEditSlot(const QString& text){
    ui->textEdit_3->setText(text);
}
void measerement_for::on_firstTypeMesageBut_clicked()
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
    ms->send_first_type_message(msg);
}

void measerement_for::on_secondTypeMesageBut_clicked()
{
    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
        ui->secondTypeMsgText->setText("Ошибка");
        return;
    }
    ui->textEdit_3->setText(QString::fromStdString(ms->recieve()));
}


void measerement_for::finish() {
    if(sock == 0) ::close(sock);
}
