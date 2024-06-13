#ifndef ACUSTIC_H
#define ACUSTIC_H


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
#include "acustic_system.h"




namespace Ui {
class acustic;
}
class acustic : public QMainWindow
{
    Q_OBJECT

public:
    explicit acustic(QWidget *parent = nullptr);
    ~acustic();

    acustic_system* acustic_sys;
    MessageReceiverThread* receiverThread=nullptr;
    void closeEvent(QCloseEvent *event);

    bool console_mode;
private slots:
    void updateTextEditSlot(const QString& text);
    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::acustic *ui;    
};


#endif // ACUSTIC_H
