#ifndef MEASEREMENT_FOR_H
#define MEASEREMENT_FOR_H

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

#include "measerement_system.h"
namespace Ui {
class measerement_for;
}

class measerement_for : public QMainWindow
{
    Q_OBJECT
public:
    explicit measerement_for(QWidget *parent = nullptr);
    ~measerement_for();
    measerement_system* ms;
    void finish();

private slots:
    void updateTextEditSlot(const QString& text);

    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::measerement_for *ui;
    const int port=37020;
    int sock;
    sockaddr_in addr;
    char buffer[1024];

    std::mutex mtx;
    std::condition_variable cv;
    bool receiveDo = false;

    MessageReceiverThread* receiverThread=nullptr;
    MessageSendThread* senderThread=nullptr;
};


#endif // MEASEREMENT_FOR_H
