#include "dist_system.h"
#include "ui_dist_system.h"

dist_system::dist_system(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dist_system)
{
    ui->setupUi(this);
}

dist_system::~dist_system()
{
    delete ui;
}
