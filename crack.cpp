#include "crack.h"
#include "ui_crack.h"

crack::crack(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::crack)
{
    ui->setupUi(this);
}

crack::~crack()
{
    delete ui;
}
