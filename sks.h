#ifndef SKS_H
#define SKS_H
#include "sks_system.h"
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
class sks;
}

class sks : public QMainWindow
{
    Q_OBJECT

public:
    explicit sks(QWidget *parent = nullptr);
    ~sks();
    void finish();
    sks_system* sks_sender;
    void closeEvent(QCloseEvent *event);
private slots:
    void updateTextEditSlot(const QString& text);

    void on_firstTypeMsgBut_clicked();

    void on_secondTypeMsgBut_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::sks *ui;
    int sock;
    sockaddr_in addr;
    char buffer[1024];

    std::mutex mtx;
    std::condition_variable cv;
    bool receiveDo = false;

    MessageReceiverThread* receiverThread=nullptr;
    MessageSendThread* senderThread=nullptr;
};

#endif // SKS_H
