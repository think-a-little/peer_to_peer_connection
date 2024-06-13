#ifndef CONSOLEREADER_H
#define CONSOLEREADER_H

#include <QTextStream>
#include <iostream>
#include <QThread>

class ConsoleReader : public QObject {
    Q_OBJECT

public:
    explicit ConsoleReader(QObject *parent = nullptr);
    void reader() {readConsole();}

signals:
    void consoleModeChanged(bool mode);

private slots:
    void readConsole() {
        bool console_mode = false;
        std::cin >> console_mode;
        emit consoleModeChanged(console_mode);
    }
};


#endif // CONSOLEREADER_H
