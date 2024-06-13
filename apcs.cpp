#include "apcs.h"
#include "ui_apcs.h"
#include <regex>
#include "srj_consts.h"
apcs::apcs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::apcs)
{
    ui->setupUi(this);

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
    QString s= ui->textEdit_3->toPlainText();
    s=s+as->recieve( text);
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

}
void apcs::finish() {
    if(sock == 0) ::close(sock);
}



//void apcs::handleMessageSend()
//{
//    QByteArray ba = ui->firstTypeMsgText->toPlainText().toLatin1();
//    char* ch = ba.data();
//    for(int i=0; i<1024; i++) buffer[i]=ch[i];
//}
//void apcs::handleMessageReceived(const QString& message)
//{
//    ui->textEdit_3->insertPlainText(message+'\n');
//}

