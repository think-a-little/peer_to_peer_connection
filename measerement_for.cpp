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
void measerement_for::updateTextEditSlot(const QString& text){
    ui->textEdit_3->setText(ms->recieve( text));
}
measerement_for::~measerement_for()
{
    delete ui;
}


void measerement_for::on_firstTypeMesageBut_clicked()
{
    std::regex pattern("[0-6]{1,480}");
    if (!(std::regex_match(ui->firstTypeMsgText->toPlainText().toStdString(),pattern))){
        ui->firstTypeMsgText->setText("Ошибка");
        return;
    }
    std::string msg = ui->firstTypeMsgText->toPlainText().toStdString();
    ms->send_first_type_message(msg);
}

void measerement_for::on_secondTypeMesageBut_clicked()
{

}

