#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sks.h"
#include "tenzometria.h"
#include "dist_system.h"
#include "ui_dist_system.h"
#include "apcs_system.h"
#include <qdebug.h>
#include "srj_consts.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*acustic_form = new acustic(new QWidget())*/;
//    crack_form = new crack(new QWidget());
//    apcs_form = new apcs(new QWidget());
//    stabilization_form = new stabilization(new QWidget());
//    measerement_form = new  measerement_for(new QWidget());
//    tenzometria_form = new tenzometria(new QWidget());
//    dist_system_form = new dist_system(new QWidget());
//    sks_form = new sks(new QWidget());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sksButton_clicked()
{
    sks_form = new sks(new QWidget());
    this->hide();
    sks_form->sks_sender = new sks_system();
     sks_form->show();
     sks_form->console_mode=console_mode;
}

void MainWindow::on_APCS_button_clicked()
{
    apcs_form = new apcs(new QWidget());
    this->hide();
    apcs_form->show();
    apcs_form->as = new apcs_system(ui->flight_type_text->toPlainText().toUInt(),
                                    ui->flight_number_text->toPlainText().toInt(),
                                    ui->cikl_number_text->toPlainText().toInt(),
                                    ui->segment_number_text->toPlainText().toUInt());
    apcs_form->console_mode=console_mode;
}

void MainWindow::on_measerement_system_button_clicked()
{
    measerement_form = new  measerement_for(new QWidget());
    this->hide();
    measerement_form->ms = new measerement_system(SYSTEM_MEASUREMENT_MOVEMENT);
    measerement_form->show();
    measerement_form->console_mode=console_mode;

}

void MainWindow::on_stabilization_system_button_clicked()
{
     stabilization_form = new stabilization(new QWidget());
    this->hide();
    stabilization_form->stab_sys = new stabilization_system(SYSTEM_OF_STABILIZATION);
    stabilization_form->show();
    stabilization_form->console_mode=console_mode;
    ConsoleReader reader;
    QThread thread(&reader);
    thread.start();


    QObject::connect(&reader, &ConsoleReader::consoleModeChanged, [this](bool mode) {
        qDebug() << "Стаб режим: " << mode;
        console_mode=mode;
        // Здесь можно добавить дополнительную логику, например, скрыть главное окно,
        // если консольный режим включен, или выполнить какие-то действия в зависимости от режима
    });
    reader.reader();
}

void MainWindow::on_tenzometria_button_clicked()
{
    tenzometria_form = new tenzometria(new QWidget());
    this->hide();
    tenzometria_form->tenz_sys= new tenzometria_system(LBORDER_SYSTEM_TENZOMETRIA);
    tenzometria_form->show();
    tenzometria_form->console_mode=console_mode;
}

void MainWindow::on_dist_sys_button_clicked()
{
//    dist_system_form = new dist_system(new QWidget());
//    this->hide();
//     dist_system_form->sd = new system_dist(LBORDER_SUBSYSTEM_DIST_VIS_WATCH);
//     dist_system_form->show();
    distant_form= new distant(new QWidget());
    distant_form->sd=new system_dist(LBORDER_SUBSYSTEM_DIST_VIS_WATCH);
    distant_form->show();
    distant_form->console_mode=console_mode;
}

void MainWindow::on_crack_sys_button_clicked()
{
    crack_form = new crack(new QWidget());
    this->hide();
     crack_form->cs = new crack_system(LBORDER_SUBSYSTEM_REGISTER_CRACK);
     crack_form->show();
     crack_form->console_mode=console_mode;
}

void MainWindow::on_acustic_sys_button_clicked()
{
    acustic_form = new acustic(new QWidget());
    this->hide();
     acustic_form->acustic_sys= new acustic_system(LBORDER_ACUSTIC_SYSTEM);
      acustic_form->show();
      acustic_form->console_mode=console_mode;
}
