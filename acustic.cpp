#include "acustic.h"
#include "ui_acustic.h"

acustic::acustic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::acustic)
{
    ui->setupUi(this);
}

acustic::~acustic()
{
    delete ui;
}
