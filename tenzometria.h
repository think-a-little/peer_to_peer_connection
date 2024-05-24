#ifndef TENZOMETRIA_H
#define TENZOMETRIA_H

#include <QMainWindow>

namespace Ui {
class tenzometria;
}

class tenzometria : public QMainWindow
{
    Q_OBJECT

public:
    explicit tenzometria(QWidget *parent = nullptr);
    ~tenzometria();

private slots:
    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::tenzometria *ui;
};

#endif // TENZOMETRIA_H
