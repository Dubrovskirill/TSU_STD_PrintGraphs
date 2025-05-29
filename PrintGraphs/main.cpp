#include "sqlitedatasource.h"
#include <QCoreApplication>
#include <QDebug>

void testDatabase(const QString& dbPath)
{
    qDebug() << "Testing database:" << dbPath;
    SqliteDataSource dataSource;

    bool success = dataSource.loadData(dbPath);
    if (!success) {
        qDebug() << "Error loading data:" << dataSource.getError();
        return;
    }

    QList<QPointF> data = dataSource.getData();
    qDebug() << "Loaded" << data.size() << "points (x in hours):";
    for (const QPointF& point : data) {
        qDebug() << "x:" << point.x() << "y:" << point.y();
    }
    qDebug() << "------------------------";
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    testDatabase("HUMIDITY_MOSCOW.sqlite");


    return 0;
}
