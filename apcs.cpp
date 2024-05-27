#include "apcs.h"
#include "ui_apcs.h"
#include <regex>

apcs::apcs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::apcs)
{
    ui->setupUi(this);

}

apcs::~apcs()
{
    delete ui;
}

void apcs::on_firstTypeMesageBut_clicked()
{
    std::regex pattern("[0-6]{1,480}");
    if (!(std::regex_match(ui->firstTypeMsgText->toPlainText().toStdString(),pattern))){
        ui->firstTypeMsgText->setText("Ошибка");
        return;
    }
}

void apcs::on_secondTypeMesageBut_clicked()
{
    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
        ui->secondTypeMsgText->setText("Ошибка");
        return;
    }

}
