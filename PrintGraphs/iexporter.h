#ifndef IEXPORTER_H
#define IEXPORTER_H

#include <QString>
#include <QChartView>

class IExporter
{
public:
    virtual ~IExporter() = default;

    // Экспорт графика в файл
    virtual bool exportToFile(const QString& filePath, QtCharts::QChartView* chartView) = 0;

    // Получение фильтра файлов для диалога сохранения
    virtual QString getFileFilter() const = 0;

    // Получение названия формата
    virtual QString getFormatName() const = 0;
};

#endif // IEXPORTER_H 