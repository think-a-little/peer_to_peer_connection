#ifndef MEASEREMENT_FOR_H
#define MEASEREMENT_FOR_H

#include <QMainWindow>

namespace Ui {
class measerement_for;
}

class measerement_for : public QMainWindow
{
    Q_OBJECT

public:
    explicit measerement_for(QWidget *parent = nullptr);
    ~measerement_for();

private slots:
    void on_firstTypeMesageBut_clicked();

    void on_secondTypeMesageBut_clicked();

private:
    Ui::measerement_for *ui;
};

#endif // MEASEREMENT_FOR_H
