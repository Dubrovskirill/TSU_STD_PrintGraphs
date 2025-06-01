#include "mainwindow.h"
#include "ioccontainer.h"

#include <QApplication>

// Определение глобального экземпляра контейнера
IOCContainer gContainer;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
