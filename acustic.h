#ifndef ACUSTIC_H
#define ACUSTIC_H

#include <QMainWindow>

namespace Ui {
class acustic;
}

class acustic : public QMainWindow
{
    Q_OBJECT

public:
    explicit acustic(QWidget *parent = nullptr);
    ~acustic();

private slots:

    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::acustic *ui;
};

#endif // ACUSTIC_H
