#include "sks.h"
#include "ui_sks.h"
#include <regex>
sks::sks(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sks)
{
    ui->setupUi(this);
}

sks::~sks()
{
    delete ui;
}
void sks::on_firstTypeMsgBut_clicked()
{
    std::regex pattern("[0-6]{1,480}");
    if (!(std::regex_match(ui->firstTypeMsgText->toPlainText().toStdString(),pattern))){
        ui->firstTypeMsgText->setText("Ошибка");
        return;
    }
    std::string msg = ui->firstTypeMsgText->toPlainText().toStdString();
    sks_sender=new sks_system();
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
