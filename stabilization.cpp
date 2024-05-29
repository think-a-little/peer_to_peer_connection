#include "stabilization.h"
#include "ui_stabilization.h"
#include <regex>
stabilization::stabilization(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::stabilization)
{
    ui->setupUi(this);
}

stabilization::~stabilization()
{
    delete ui;
}

void stabilization::on_firstTypeMesageBut_clicked()
{
    std::regex pattern("[0-6]{1,480}");
    if (!(std::regex_match(ui->firstTypeMsgText->toPlainText().toStdString(),pattern))){
        ui->firstTypeMsgText->setText("Ошибка");
        return;
    }
    stab_sys->send_first_type_message(ui->firstTypeMsgText->toPlainText().toStdString());
}

void stabilization::on_secondTypeMesageBut_clicked()
{
    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
        ui->secondTypeMsgText->setText("Ошибка");
        return;
    }
}
