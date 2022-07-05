#include "mainwindow.h"

#include <QApplication>
#include <QSharedMemory>

int main(int argc, char* argv[])
{
    QSharedMemory shared("GameControlKit"); //随便填个名字就行
    if (shared.attach())
        return 0;
    shared.create(1);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
