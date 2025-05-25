#ifndef IOCSETUP_H
#define IOCSETUP_H


#include "ioccontainer.h"
#include "datasource.h"
#include "graphrendere.h"
#include "pdfexporter.h"

void setupIoC(IoCContainer& container)
{
    // Регистрация заглушки для IDataSource (будет заменена на SqliteDataSource или JsonDataSource)
    container.registerType<IDataSource>([]() -> QSharedPointer<IDataSource> {
        return nullptr; // Заглушка, реализация позже
    });

    // Регистрация заглушки для IGraphRenderer
    container.registerType<IGraphRenderer>([]() -> QSharedPointer<IGraphRenderer> {
        return nullptr; // Заглушка
    });

    // Регистрация заглушки для IPdfExporter
    container.registerType<IPdfExporter>([]() -> QSharedPointer<IPdfExporter> {
        return nullptr; // Заглушка
    });
}

#endif // IOCSETUP_H
