#include "mainwindow.h"
#include "ioccontainer.h"
#include "iocsetup.h"

#include <QApplication>

// Определение глобального экземпляра контейнера
IOCContainer gContainer;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Инициализация IOC контейнера
    setupIoC();

    MainWindow w;
    w.show();
    return a.exec();
}
