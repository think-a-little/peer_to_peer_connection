#include "measerement_for.h"
#include "ui_measerement_for.h"
#include <regex>
measerement_for::measerement_for(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::measerement_for)
{
    ui->setupUi(this);
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
    ms->send_first_type_message(ui->firstTypeMsgText->toPlainText().toStdString());
}

void measerement_for::on_secondTypeMesageBut_clicked()
{
    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
        ui->secondTypeMsgText->setText("Ошибка");
        return;
    }
    ui->textEdit_3->setText(QString::fromStdString(ms->recieve()));
}



