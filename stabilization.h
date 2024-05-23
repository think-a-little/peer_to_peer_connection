#ifndef STABILIZATION_H
#define STABILIZATION_H

#include <QWidget>

namespace Ui {
class stabilization;
}

class stabilization : public QWidget
{
    Q_OBJECT

public:
    explicit stabilization(QWidget *parent = nullptr);
    ~stabilization();

private:
    Ui::stabilization *ui;
};

#endif // STABILIZATION_H
