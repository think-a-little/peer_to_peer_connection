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
    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
        ui->secondTypeMsgText->setText("Ошибка");
        return;
    }
    ms->send_second_type_message(ui->secondTypeMsgText->toPlainText().toStdString());
}

void measerement_for::closeEvent(QCloseEvent *event)
{
    ms->send_fourth_type_message();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if(ms) delete ms;
    qDebug()<<"окно закрывается";
    QWidget::closeEvent(event);
}


