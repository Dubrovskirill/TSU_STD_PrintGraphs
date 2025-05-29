#ifndef SQLITEDATASOURCE_H
#define SQLITEDATASOURCE_H

#include "datasource.h"
#include <QSqlDatabase>
#include <QString>
#include <QDateTime>

class SqliteDataSource : public IDataSource
{
public:
    SqliteDataSource();
    ~SqliteDataSource() override;

    bool loadData(const QString& sourcePath) override;
    QList<QPointF> getData() const override;
    QString getError() const override;

private:
    QSqlDatabase m_db;
    QList<QPointF> m_data;
    QString m_error;
};

#endif // SQLITEDATASOURCE_H
