#ifndef DIST_SYSTEM_H
#define DIST_SYSTEM_H

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
class dist_system;
}

class dist_system : public QWidget
{
    Q_OBJECT

public:
    explicit dist_system(QWidget *parent = nullptr);
    ~dist_system();
    system_dist* sd;
    MessageReceiverThread* receiverThread=nullptr;
private slots:
    void updateTextEditSlot(const QString& text);
    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::dist_system *ui;
};

#endif // DIST_SYSTEM_H
