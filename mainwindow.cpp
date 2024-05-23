#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sks.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sk = new sks(new QWidget());
 }

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_sksButton_clicked()
{
    this->hide();
    sk->show();
}
