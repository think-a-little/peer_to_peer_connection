#include "apcs.h"
#include "ui_APCS.h"

APCS::APCS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::APCS)
{
    ui->setupUi(this);
}

APCS::~APCS()
{
    delete ui;
}
