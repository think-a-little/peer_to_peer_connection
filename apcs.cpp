#include "apcs.h"
#include "ui_apcs.h"
#include <regex>
#include "srj_consts.h"
apcs::apcs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::apcs)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    if (!receiverThread) {
        receiverThread = new MessageReceiverThread(this);
        connect(receiverThread, &MessageReceiverThread::messageReceived, this, &apcs::updateTextEditSlot);
    }
    receiverThread->start();
}

apcs::~apcs()
{
    delete ui;
    finish();
}
void apcs::updateTextEditSlot(const QString& text){
//    ui->textEdit_3->setText(as->recieve(text));
    QString s= as->recieve( text);
    s=s+ui->textEdit_3->toPlainText();
    ui->textEdit_3->setText(s);
    qDebug()<<"вывели"<< text;
}


void apcs::on_firstTypeMesageBut_clicked()
{
    std::regex pattern("[0-6]{1,480}");
    if (!(std::regex_match(ui->firstTypeMsgText->toPlainText().toStdString(),pattern))){
        ui->firstTypeMsgText->setText("Ошибка");
        return;
    }

    std::string msg =ui->firstTypeMsgText->toPlainText().toStdString();
    as->send_first_type_message(msg);

}

void apcs::on_secondTypeMesageBut_clicked()
{
    std::regex pattern("[a-zA-Z0-5-/]{1,16}");
    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
        ui->secondTypeMsgText->setText("Ошибка");
        return;
    }
    as->send_second_type_message(ui->secondTypeMsgText->toPlainText().toStdString());
}
void apcs::finish() {
    if(sock == 0) ::close(sock);
}

void apcs::closeEvent(QCloseEvent *event)
{
    as->send_fourth_type_message();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if(as) delete as;
    qDebug()<<"окно закрывается";
    QWidget::closeEvent(event);
}




