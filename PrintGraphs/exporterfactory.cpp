#include "exporterfactory.h"
#include "pdfexporter.h"
#include "jpegexporter.h"

QSharedPointer<IExporter> ExporterFactory::createExporter(const QString& format)
{
    if (format.toUpper() == "PDF") {
        return QSharedPointer<IExporter>(new PdfExporter());
    }
    else if (format.toUpper() == "JPEG") {
        return QSharedPointer<IExporter>(new JpegExporter());
    }
    return nullptr;
}

QStringList ExporterFactory::getAvailableFormats()
{
    return {"PDF", "JPEG"};
} 