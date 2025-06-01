#ifndef IOCSETUP_H
#define IOCSETUP_H

#include "ioccontainer.h"
#include "igraphrenderer.h"
#include "graphrenderer.h"
#include "datasource.h"
#include "sqlitedatasource.h"
#include "jsondatasource.h"
#include "iexporter.h"
#include "pdfexporter.h"
#include "jpegexporter.h"

// Функция для настройки IOC контейнера
inline void setupIoC()
{
    // Регистрация GraphRenderer как реализации IGraphRenderer
    gContainer.RegisterFactory<IGraphRenderer, GraphRenderer>();

    // Регистрация источников данных
    gContainer.RegisterFactory<IDataSource, SqliteDataSource>();
    gContainer.RegisterFactory<IDataSource, JsonDataSource>();

    // Регистрация экспортеров
    gContainer.RegisterFactory<IExporter, PdfExporter>();
    gContainer.RegisterFactory<IExporter, JpegExporter>();
}

#endif // IOCSETUP_H 