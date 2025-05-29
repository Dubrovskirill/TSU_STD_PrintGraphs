#ifndef JSONDATASOURCE_H
#define JSONDATASOURCE_H

#include "datasource.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>

class JsonDataSource : public IDataSource
{
public:
    JsonDataSource() = default;
    ~JsonDataSource() override = default;

    bool loadData(const QString& sourcePath) override;
    QList<QPointF> getData() const override;
    QString getError() const override;

private:
    QList<QPointF> m_data;
    QString m_error;
    
    // Вспомогательные методы для валидации данных
    bool validateJsonFormat(const QJsonArray& array);
    bool parseDateTime(const QString& dateTimeStr, QDateTime& dateTime);
};

#endif // JSONDATASOURCE_H 