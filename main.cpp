#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QTextStream in(stdin);
        QTextStream out(stdout);

        ConsoleReader reader;
        QThread thread(&reader);
        thread.start();


        QObject::connect(&reader, &ConsoleReader::consoleModeChanged, [&w](bool mode) {
            qDebug() << "Консольный режим: " << mode;
            w.console_mode=mode;
            // Здесь можно добавить дополнительную логику, например, скрыть главное окно,
            // если консольный режим включен, или выполнить какие-то действия в зависимости от режима
        });
        reader.reader();

    w.show();
    return a.exec();
}
