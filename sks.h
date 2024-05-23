#ifndef SKS_H
#define SKS_H

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

private slots:


    void on_firstTypeMsgBut_clicked();

    void on_secondTypeMsgBut_clicked();

private:
    Ui::sks *ui;
};

#endif // SKS_H
