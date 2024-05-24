#ifndef STABILIZATION_H
#define STABILIZATION_H

#include <QMainWindow>

namespace Ui {
class stabilization;
}

class stabilization : public QMainWindow
{
    Q_OBJECT

public:
    explicit stabilization(QWidget *parent = nullptr);
    ~stabilization();

private slots:
    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::stabilization *ui;
};

#endif // STABILIZATION_H
