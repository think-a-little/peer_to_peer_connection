#ifndef DISTANT_H
#define DISTANT_H

#include <QMainWindow>
#include <QWidget>
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

#include "system_dist.h"
namespace Ui {
class distant;
}

class distant : public QMainWindow
{
    Q_OBJECT

public:
    explicit distant(QWidget *parent = nullptr);
    ~distant();
    system_dist* sd;
    MessageReceiverThread* receiverThread=nullptr;
private slots:
    void updateTextEditSlot(const QString& text);
    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::distant *ui;
};

#endif // DISTANT_H
