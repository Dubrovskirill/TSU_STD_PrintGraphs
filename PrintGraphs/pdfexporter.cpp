#include "pdfexporter.h"
#include <QPainter>

bool PdfExporter::exportToFile(const QString& filePath, QtCharts::QChartView* chartView)
{
    if (!chartView) {
        return false;
    }

    QPdfWriter pdfWriter(filePath);
    QPainter painter(&pdfWriter);
    chartView->render(&painter);
    return true;
}

QString PdfExporter::getFileFilter() const
{
    return "PDF (*.pdf)";
}

QString PdfExporter::getFormatName() const
{
    return "PDF";
} 