#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "apcs.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AS= new APCS(1,1,1,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool rcd=true;

void MainWindow::on_pushButton_4_clicked()
{

    AS->receive();

}
