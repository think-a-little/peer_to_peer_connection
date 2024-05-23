#include "measerement_for.h"
#include "ui_measerement_for.h"

measerement_for::measerement_for(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::measerement_for)
{
    ui->setupUi(this);
}

measerement_for::~measerement_for()
{
    delete ui;
}
