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

    // Регистрация источников данных с ключами-расширениями
    gContainer.RegisterFactory<IDataSource, SqliteDataSource>("sqlite");
    gContainer.RegisterFactory<IDataSource, JsonDataSource>("json");

    // Регистрация экспортеров с ключами-форматами
    gContainer.RegisterFactory<IExporter, PdfExporter>("pdf");
    gContainer.RegisterFactory<IExporter, JpegExporter>("jpeg");
}

#endif // IOCSETUP_H