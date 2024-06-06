#include "dist_system.h"
#include "ui_dist_system.h"
#include <regex>
dist_system::dist_system(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dist_system)
{
    ui->setupUi(this);
}

dist_system::~dist_system()
{
    delete ui;
}


void dist_system::on_firstTypeMesageBut_clicked()
{
    std::regex pattern("[0-6]{1,480}");
    if (!(std::regex_match(ui->firstTypeMsgText->toPlainText().toStdString(),pattern))){
        ui->firstTypeMsgText->setText("Ошибка");
        return;
    }
    sd->send_first_type_message(ui->firstTypeMsgText->toPlainText().toStdString());
}

void dist_system::on_secondTypeMesageBut_clicked()
{
    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
        ui->secondTypeMsgText->setText("Ошибка");
        return;
    }
    ui->textEdit_3->setText(QString::fromStdString(sd->recieve()));
}
