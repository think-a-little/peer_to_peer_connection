#ifndef APCS_H
#define APCS_H

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
#include "apcs_system.h"
#include "messagesendthread.h"
#include <QApplication>
#include <QThread>
#include <QTimer>
#include <QTextStream>

namespace Ui {


class apcs;
}
class apcs : public QMainWindow
{
    Q_OBJECT

public:
    apcs_system* as;
    uint8_t id_message=1;
    explicit apcs(QWidget *parent = nullptr);
    ~apcs();
    void con();
    void finish();

    void receive();

    void send(std::string message);
private:
    Ui::apcs *ui;
    int sock;
    sockaddr_in addr;
    char buffer[1024];

    std::mutex mtx;
    std::condition_variable cv;
    bool receiveDo = false;

    MessageReceiverThread* receiverThread=nullptr;
    MessageSendThread* senderThread=nullptr;
private slots:
    void updateTextEditSlot(const QString& text) ;

    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();


};

#endif // APCS_H
