#include "acustic.h"
#include "ui_acustic.h"
#include <regex>

acustic::acustic(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::acustic)
{
    ui->setupUi(this);
    if (!receiverThread) {
        receiverThread = new MessageReceiverThread(this);
        connect(receiverThread, &MessageReceiverThread::messageReceived, this, &acustic::updateTextEditSlot);
    }
    receiverThread->start();
}
void acustic::updateTextEditSlot(const QString& text){
    ui->textEdit_3->setText(acustic_sys->recieve( text));
}
acustic::~acustic()
{
    delete ui;
}


void acustic::on_firstTypeMesageBut_clicked()
{
    std::regex pattern("[0-6]{1,480}");
    if (!(std::regex_match(ui->firstTypeMsgText->toPlainText().toStdString(),pattern))){
        ui->firstTypeMsgText->setText("Ошибка");
        return;
    }
    acustic_sys->send_first_type_message(ui->firstTypeMsgText->toPlainText().toStdString());
}

void acustic::on_secondTypeMesageBut_clicked()
{

}

