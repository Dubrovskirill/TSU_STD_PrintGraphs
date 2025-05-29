#ifndef DATASOURCEFACTORY_H
#define DATASOURCEFACTORY_H

#include "datasource.h"
#include "sqlitedatasource.h"
#include "jsondatasource.h"
#include <QSharedPointer>

class DataSourceFactory
{
public:
    static QSharedPointer<IDataSource> createSource(const QString& filePath)
    {
        if (filePath.endsWith(".sqlite", Qt::CaseInsensitive)) {
            return QSharedPointer<IDataSource>(new SqliteDataSource());
        } else if (filePath.endsWith(".json", Qt::CaseInsensitive)) {
            return QSharedPointer<IDataSource>(new JsonDataSource());
        }
        return nullptr;
    }
};

#endif // DATASOURCEFACTORY_H
