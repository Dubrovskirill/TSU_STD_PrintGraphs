#ifndef PDFEXPORTER_H
#define PDFEXPORTER_H

#include <QString>

// Интерфейс для экспорта в PDF
class IPdfExporter
{
public:
    virtual ~IPdfExporter() = default;
    virtual bool exportToPdf(const QString& filePath) = 0;
    virtual QString getError() const = 0;
};

#endif // PDFEXPORTER_H
