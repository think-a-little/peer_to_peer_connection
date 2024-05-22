#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sks.h"
#include "apcs.h"
#include "measerement_for.h"
#include "stabilization.h"
#include "acustic.h"
#include "crack.h"
#include "dist_system.h"
#include "tenzometria.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    APCS *apcs_form;
    stabilization *stabilization_form;
    measerement_for *measerement_form;
    sks *sks_form;
    acustic *acustic_form;
    crack *crack_form;
    dist_system *dist_system_form;
    tenzometria *tenzometria_form;
private slots:

    void on_sksButton_clicked();

    void on_APCS_button_clicked();

    void on_measerement_system_button_clicked();

    void on_stabilization_system_button_clicked();

    void on_tenzometria_button_clicked();

    void on_dist_sys_button_clicked();

    void on_crack_sys_button_clicked();

    void on_acustic_sys_button_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
