#ifndef DIST_SYSTEM_H
#define DIST_SYSTEM_H

#include <QWidget>

namespace Ui {
class dist_system;
}

class dist_system : public QWidget
{
    Q_OBJECT

public:
    explicit dist_system(QWidget *parent = nullptr);
    ~dist_system();

private:
    Ui::dist_system *ui;
};

#endif // DIST_SYSTEM_H
