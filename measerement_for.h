#ifndef MEASEREMENT_FOR_H
#define MEASEREMENT_FOR_H

#include <QWidget>

namespace Ui {
class measerement_for;
}

class measerement_for : public QWidget
{
    Q_OBJECT

public:
    explicit measerement_for(QWidget *parent = nullptr);
    ~measerement_for();

private:
    Ui::measerement_for *ui;
};

#endif // MEASEREMENT_FOR_H
