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

void acustic::closeEvent(QCloseEvent *event)
{
    acustic_sys->send_fourth_type_message();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if(acustic_sys) delete acustic_sys;
    qDebug()<<"окно закрывается";
    QWidget::closeEvent(event);
}

