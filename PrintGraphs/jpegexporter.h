#ifndef JPEGEXPORTER_H
#define JPEGEXPORTER_H

#include "iexporter.h"
#include <QImage>

class JpegExporter : public IExporter
{
public:
    JpegExporter() = default;
    ~JpegExporter() override = default;

    bool exportToFile(const QString& filePath, QtCharts::QChartView* chartView) override;
    QString getFileFilter() const override;
    QString getFormatName() const override;

private:
    QString ensureJpegExtension(const QString& filePath) const;
};

#endif // JPEGEXPORTER_H 