#ifndef PDFEXPORTER_H
#define PDFEXPORTER_H

#include "iexporter.h"
#include <QPdfWriter>

class PdfExporter : public IExporter
{
public:
    PdfExporter() = default;
    ~PdfExporter() override = default;

    bool exportToFile(const QString& filePath, QtCharts::QChartView* chartView) override;
    QString getFileFilter() const override;
    QString getFormatName() const override;
};

#endif // PDFEXPORTER_H 