#include "sqlitedatasource.h"
#include "jsondatasource.h"
#include <QCoreApplication>
#include <QDebug>

void testDatabase(const QString& dbPath)
{
    qDebug() << "Testing SQLite database:" << dbPath;
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

void testJson(const QString& jsonPath)
{
    qDebug() << "Testing JSON file:" << jsonPath;
    JsonDataSource dataSource;

    bool success = dataSource.loadData(jsonPath);
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

    // Тестируем SQLite источник
     testDatabase("D:/STD/TSU_STD_PrintGraphs/PrintGraphs/InputData/TEMPERATURE_NOVOSIB.sqlite");

    // Тестируем JSON источник
    //testJson("D:/STD/TSU_STD_PrintGraphs/PrintGraphs/InputData/TEMPERATURE_NOVOSIB.json");

    return 0;
}
