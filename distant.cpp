#include "distant.h"
#include "ui_distant.h"
#include <regex>

distant::distant(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::distant)
{
    ui->setupUi(this);
    qDebug()<<"sxas";
    if (!receiverThread) {
        receiverThread = new MessageReceiverThread(this);
        connect(receiverThread, &MessageReceiverThread::messageReceived, this, &distant::updateTextEditSlot);
    }
    receiverThread->start();
}
void distant::updateTextEditSlot(const QString& text){
    ui->textEdit_3->setText(sd->recieve( text));
}
distant::~distant()
{
    delete ui;
}


void distant::on_firstTypeMesageBut_clicked()
{
    std::regex pattern("[0-6]{1,480}");
    if (!(std::regex_match(ui->firstTypeMsgText->toPlainText().toStdString(),pattern))){
        ui->firstTypeMsgText->setText("Ошибка");
        return;
    }
    sd->send_first_type_message(ui->firstTypeMsgText->toPlainText().toStdString());
}

void distant::on_secondTypeMesageBut_clicked()
{
    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
        ui->secondTypeMsgText->setText("Ошибка");
        return;
    }
    sd->send_second_type_message(ui->secondTypeMsgText->toPlainText().toStdString());
}
