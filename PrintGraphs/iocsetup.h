#ifndef IOCSETUP_H
#define IOCSETUP_H

#include "ioccontainer.h"
#include "datasource.h"
#include "sqlitedatasource.h"
#include "graphrenderer.h"
#include "pdfexporter.h"

void setupIoC(IoCContainer& container)
{
    // Регистрация SqliteDataSource как реализации IDataSource
    container.registerType<IDataSource>([]() -> QSharedPointer<IDataSource> {
        return QSharedPointer<IDataSource>(new SqliteDataSource());
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
