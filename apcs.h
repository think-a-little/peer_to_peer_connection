#ifndef APCS_H
#define APCS_H

#include <QMainWindow>

namespace Ui {
class apcs;
}

class apcs : public QMainWindow
{
    Q_OBJECT

public:
    explicit apcs(QWidget *parent = nullptr);
    ~apcs();

private slots:
    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::apcs *ui;
};

#endif // APCS_H
