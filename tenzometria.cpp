#include "tenzometria.h"
#include "ui_tenzometria.h"
#include <regex>
tenzometria::tenzometria(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tenzometria)
{
    ui->setupUi(this);
}

tenzometria::~tenzometria()
{
    delete ui;
}

void tenzometria::on_firstTypeMesageBut_clicked()
{
    std::regex pattern("[0-6]{1,480}");
    if (!(std::regex_match(ui->firstTypeMsgText->toPlainText().toStdString(),pattern))){
        ui->firstTypeMsgText->setText("Ошибка");
        return;
    }

        std::string msg = ui->firstTypeMsgText->toPlainText().toStdString();
        tenz_sys=new tenzometria_system(LBORDER_SYSTEM_TENZOMETRIA);
        tenz_sys->send_first_type_message(msg);
}

void tenzometria::on_secondTypeMesageBut_clicked()
{
    std::regex pattern("[a-zA-Z0-5-/]{1,1}");
    if (!(std::regex_match(ui->secondTypeMsgText->toPlainText().toStdString(),pattern)) ||(ui->secondTypeMsgText->toPlainText().length()>1 )){
        ui->secondTypeMsgText->setText("Ошибка");
        return;
    }
}
