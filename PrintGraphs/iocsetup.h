#ifndef IOCSETUP_H
#define IOCSETUP_H

#include "ioccontainer.h"
#include "datasource.h"
#include "sqlitedatasource.h"
#include "graphrendere.h"
#include "pdfexporter.h"

void setupIoC(IoCContainer& container)
{
    // Регистрация SqliteDataSource как реализации IDataSource
    container.registerType<IDataSource>([]() -> QSharedPointer<IDataSource> {
        return QSharedPointer<IDataSource>(new SqliteDataSource());
    });

    // Заглушки для IGraphRenderer и IPdfExporter
    container.registerType<IGraphRenderer>([]() -> QSharedPointer<IGraphRenderer> {
        return nullptr;
    });

    container.registerType<IPdfExporter>([]() -> QSharedPointer<IPdfExporter> {
        return nullptr;
    });
}

#endif // IOCSETUP_H
