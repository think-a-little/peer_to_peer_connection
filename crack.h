#ifndef CRACK_H
#define CRACK_H

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

#include "crack_system.h"
namespace Ui {
class crack;
}
class crack : public QMainWindow
{
    Q_OBJECT

public:
    explicit crack(QWidget *parent = nullptr);
    ~crack();
    crack_system* cs;
private slots:
    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::crack *ui;
};
#endif // CRACK_H
