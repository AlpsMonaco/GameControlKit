#include "mainwindow.h"

#include <QApplication>
#include <QSharedMemory>

int main(int argc, char* argv[])
{
    QSharedMemory shared_momory("GameControlKit"); //随便填个名字就行
    if (shared_momory.attach())
        return 0;
    shared_momory.create(1);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
