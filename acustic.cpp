#include "acustic.h"
#include "ui_acustic.h"
#include <regex>
acustic::acustic(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::acustic)
{
    ui->setupUi(this);
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
}

void acustic::on_secondTypeMesageBut_clicked()
{
    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
        ui->secondTypeMsgText->setText("Ошибка");
        return;
    }
}
