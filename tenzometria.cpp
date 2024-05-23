#include "tenzometria.h"
#include "ui_tenzometria.h"

tenzometria::tenzometria(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tenzometria)
{
    ui->setupUi(this);
}

tenzometria::~tenzometria()
{
    delete ui;
}
