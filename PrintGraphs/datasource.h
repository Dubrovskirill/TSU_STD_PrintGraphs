#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QList>
#include <QPointF>
#include <QString>
// Интерфейс источника данных
class IDataSource
{
public:
    virtual ~IDataSource() = default;
    virtual bool loadData(const QString& sourcePath) = 0;
    virtual QList<QPointF> getData() const = 0;
    virtual QString getError() const = 0;
};

#endif // DATASOURCE_H
