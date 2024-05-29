#ifndef STABILIZATION_H
#define STABILIZATION_H
#include <QThread>
#include <QMainWindow>

#include <QMainWindow>
#include <QThread>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <QDebug>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "protsrj.h"
#include <string>
#include <unordered_map>
#include "stabilization_system.h"

namespace Ui {
class stabilization;
}

class stabilization : public QMainWindow
{
    Q_OBJECT

public:
    char buffer[1024];
    explicit stabilization(QWidget *parent = nullptr);
    ~stabilization();
    stabilization_system* stab_sys;

private slots:
    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::stabilization *ui;
private slots:

};


#endif // STABILIZATION_H
