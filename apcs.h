#ifndef APCS_H
#define APCS_H

#include <QWidget>

namespace Ui {
class APCS;
}

class APCS : public QWidget
{
    Q_OBJECT

public:
    explicit APCS(QWidget *parent = nullptr);
    ~APCS();

private:
    Ui::APCS *ui;
};

#endif // APCS_H
