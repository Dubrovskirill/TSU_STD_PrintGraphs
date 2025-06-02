#ifndef IOCSETUP_H
#define IOCSETUP_H

#include "ioccontainer.h"
#include "igraphrenderer.h"
#include "LineGraphRenderer.h"
#include "datasource.h"
#include "sqlitedatasource.h"
#include "jsondatasource.h"
#include "iexporter.h"
#include "pdfexporter.h"
#include "jpegexporter.h"
#include "areagraphrenderer.h"

// Глобальный контейнер IOC
extern IOCContainer gContainer;

// Функция для настройки IOC контейнера
inline void setupIoC()
{
    // Регистрация источников данных
    gContainer.RegisterFactory<IDataSource, SqliteDataSource>("sqlite");
    gContainer.RegisterFactory<IDataSource, JsonDataSource>("json");

    // Регистрация рендереров графиков
    gContainer.RegisterFactory<IGraphRenderer, LineGraphRenderer>("line");
    gContainer.RegisterFactory<IGraphRenderer, AreaGraphRenderer>("area");

    // Регистрация экспортеров
    gContainer.RegisterFactory<IExporter, PdfExporter>("pdf");
    gContainer.RegisterFactory<IExporter, JpegExporter>("jpeg");
}

#endif // IOCSETUP_H
