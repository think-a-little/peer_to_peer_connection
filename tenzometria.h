#ifndef TENZOMETRIA_H
#define TENZOMETRIA_H

#include <QWidget>

namespace Ui {
class tenzometria;
}

class tenzometria : public QWidget
{
    Q_OBJECT

public:
    explicit tenzometria(QWidget *parent = nullptr);
    ~tenzometria();

private:
    Ui::tenzometria *ui;
};

#endif // TENZOMETRIA_H
