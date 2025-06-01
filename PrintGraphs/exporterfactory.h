#ifndef EXPORTERFACTORY_H
#define EXPORTERFACTORY_H

#include "iexporter.h"
#include <QString>
#include <QStringList>
#include <QSharedPointer>

class ExporterFactory
{
public:
    // Создание экспортера по названию формата
    static QSharedPointer<IExporter> createExporter(const QString& format);

    // Получение списка доступных форматов
    static QStringList getAvailableFormats();

private:
    ExporterFactory() = delete; // Запрещаем создание экземпляров
};

#endif // EXPORTERFACTORY_H 