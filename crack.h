#ifndef CRACK_H
#define CRACK_H

#include <QMainWindow>

namespace Ui {
class crack;
}

class crack : public QMainWindow
{
    Q_OBJECT

public:
    explicit crack(QWidget *parent = nullptr);
    ~crack();

private slots:
    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::crack *ui;
};

#endif // CRACK_H
