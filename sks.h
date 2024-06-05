#ifndef SKS_H
#define SKS_H
#include "sks_system.h"
#include <QMainWindow>

namespace Ui {
class sks;
}

class sks : public QMainWindow
{
    Q_OBJECT

public:
    explicit sks(QWidget *parent = nullptr);
    ~sks();
    sks_system* sks_sender;
private slots:


    void on_firstTypeMsgBut_clicked();

    void on_secondTypeMsgBut_clicked();

private:
    Ui::sks *ui;
};

#endif // SKS_H
