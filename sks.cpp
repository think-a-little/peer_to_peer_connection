#include "sks.h"
#include "ui_sks.h"
#include <regex>
sks::sks(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sks)
{
    ui->setupUi(this);
    if (!receiverThread) {
        receiverThread = new MessageReceiverThread(this);
        connect(receiverThread, &MessageReceiverThread::messageReceived, this, &sks::updateTextEditSlot);
    }
    receiverThread->start();
}

sks::~sks()
{
    delete ui;
    finish();
}

void sks::updateTextEditSlot(const QString& text){
//    QString s= ui->textEdit_3->toPlainText();
//    s=s+sks_sender->recieve( text);
//    ui->textEdit_3->setText(s);
    ui->textEdit_3->insertPlainText(sks_sender->recieve(text));
//    sks_sender->send_zero_type_message("");
    qDebug()<<"вывели"<< text;
}

void sks::on_firstTypeMsgBut_clicked()
{
    std::regex pattern("[0-6]{1,480}");
    if (!(std::regex_match(ui->firstTypeMsgText->toPlainText().toStdString(),pattern))){
        ui->firstTypeMsgText->setText("Ошибка");
        return;
    }

    std::string msg =ui->firstTypeMsgText->toPlainText().toStdString();
    sks_sender->send_first_type_message(msg);

}

void sks::on_secondTypeMsgBut_clicked()
{
    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
        ui->secondTypeMsgText->setText("Ошибка");
        return;
    }

}

void sks::finish() {
    if(sock == 0) ::close(sock);
}

