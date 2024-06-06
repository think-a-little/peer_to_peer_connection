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
void apcs::updateTextEditSlot(const QString& text){
    ui->textEdit_3->setText(text);
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
    std::string msg =ui->firstTypeMsgText->toPlainText().toStdString();
    as->send_first_type_message(msg);

}

void apcs::on_secondTypeMesageBut_clicked()
{
    //    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    //    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
    //        ui->secondTypeMsgText->setText("Ошибка");
    //        return;
    //    }
    ui->textEdit_3->setText(QString::fromStdString(as->recieve()));

}
void apcs::finish() {
    if(sock == 0) ::close(sock);
}




