#include "crack.h"
#include "ui_crack.h"
#include <regex>
crack::crack(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::crack)
{
    ui->setupUi(this);
    if (!receiverThread) {
        receiverThread = new MessageReceiverThread(this);
        connect(receiverThread, &MessageReceiverThread::messageReceived, this, &crack::updateTextEditSlot);
    }
    receiverThread->start();
}
void crack::updateTextEditSlot(const QString& text){
    ui->textEdit_3->setText(cs->recieve( text));
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
    cs->send_first_type_message(ui->firstTypeMsgText->toPlainText().toStdString());
}

void crack::on_secondTypeMesageBut_clicked()
{

}
