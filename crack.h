#ifndef CRACK_H
#define CRACK_H

#include <QWidget>

namespace Ui {
class crack;
}

class crack : public QWidget
{
    Q_OBJECT

public:
    explicit crack(QWidget *parent = nullptr);
    ~crack();

private:
    Ui::crack *ui;
};

#endif // CRACK_H
