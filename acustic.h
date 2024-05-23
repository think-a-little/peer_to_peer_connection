#ifndef ACUSTIC_H
#define ACUSTIC_H

#include <QWidget>

namespace Ui {
class acustic;
}

class acustic : public QWidget
{
    Q_OBJECT

public:
    explicit acustic(QWidget *parent = nullptr);
    ~acustic();

private:
    Ui::acustic *ui;
};

#endif // ACUSTIC_H
