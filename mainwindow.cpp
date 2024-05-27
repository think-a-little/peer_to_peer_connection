#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sks.h"
#include "tenzometria.h"
#include "dist_system.h"
#include "ui_dist_system.h"
#include "apcs_system.h"
#include <qdebug.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    acustic_form = new acustic(new QWidget());
    crack_form = new crack(new QWidget());
    apcs_form = new apcs(new QWidget());
    stabilization_form = new stabilization(new QWidget());
    measerement_form = new  measerement_for(new QWidget());
    tenzometria_form = new tenzometria(new QWidget());
    dist_system_form = new dist_system(new QWidget());
    sks_form = new sks(new QWidget());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sksButton_clicked()
{
    sks_form->show();

}

void MainWindow::on_APCS_button_clicked()
{
apcs_form->show();
apcs_system1 = new apcs_system(ui->flight_type_text->toPlainText().toUInt(),
                               ui->flight_number_text->toPlainText().toInt(),
                               ui->cikl_number_text->toPlainText().toInt(),
                               ui->segment_number_text->toPlainText().toUInt());
}

void MainWindow::on_measerement_system_button_clicked()
{
measerement_form->show();
}

void MainWindow::on_stabilization_system_button_clicked()
{
stabilization_form->show();
}

void MainWindow::on_tenzometria_button_clicked()
{

    tenzometria_form->show();

}

void MainWindow::on_dist_sys_button_clicked()
{
    dist_system_form->show();
}

void MainWindow::on_crack_sys_button_clicked()
{
    crack_form->show();
}

void MainWindow::on_acustic_sys_button_clicked()
{
    acustic_form->show();
}
