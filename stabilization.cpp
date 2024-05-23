#include "stabilization.h"
#include "ui_stabilization_form.h"

stabilization::stabilization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stabilization)
{
    ui->setupUi(this);
}

stabilization::~stabilization()
{
    delete ui;
}
