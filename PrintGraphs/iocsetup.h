#ifndef IOCSETUP_H
#define IOCSETUP_H

#include "ioccontainer.h"
#include "datasource.h"
#include "sqlitedatasource.h"
#include "jsondatasource.h"
#include "graphrenderer.h"
#include "pdfexporter.h"

void setupIoC(IoCContainer& container)
{
    // Регистрация фабрики источников данных
    container.registerType<IDataSource>([]() -> QSharedPointer<IDataSource> {
        // По умолчанию возвращаем SQLite источник
        return QSharedPointer<IDataSource>(new SqliteDataSource());
    });

    // Регистрация JsonDataSource
    container.registerType<JsonDataSource>([]() -> QSharedPointer<JsonDataSource> {
        return QSharedPointer<JsonDataSource>(new JsonDataSource());
    });

    // Регистрация GraphRenderer как реализации IGraphRenderer
    container.registerType<IGraphRenderer>([]() -> QSharedPointer<IGraphRenderer> {
        return QSharedPointer<IGraphRenderer>(new GraphRenderer());
    });

    // Заглушка для IPdfExporter
    container.registerType<IPdfExporter>([]() -> QSharedPointer<IPdfExporter> {
        return nullptr;
    });
}

#endif // IOCSETUP_H
