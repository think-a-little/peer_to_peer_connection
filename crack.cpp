#include "crack.h"
#include "ui_crack.h"
#include <regex>
crack::crack(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::crack)
{
    ui->setupUi(this);
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
    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
        ui->secondTypeMsgText->setText("Ошибка");
        return;
    }
    ui->textEdit_3->setText(QString::fromStdString(cs->recieve()));
}
