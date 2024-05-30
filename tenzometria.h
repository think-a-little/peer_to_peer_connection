#ifndef TENZOMETRIA_H
#define TENZOMETRIA_H

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
#include "tenzometria_system.h"
#include "messagesendthread.h"

namespace Ui {
class tenzometria;
}

class tenzometria : public QMainWindow
{
    Q_OBJECT

public:
    tenzometria_system* tenz_sys;
    explicit tenzometria(QWidget *parent = nullptr);
    ~tenzometria();

private slots:
    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::tenzometria *ui;
    const int port=37020;
    int sock;
    sockaddr_in addr;
    char buffer[1024];

    std::mutex mtx;
    std::condition_variable cv;
    bool receiveDo = false;


};

#endif // TENZOMETRIA_H
