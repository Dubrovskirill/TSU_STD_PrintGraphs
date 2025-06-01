#include "jpegexporter.h"
#include <QPainter>

bool JpegExporter::exportToFile(const QString& filePath, QtCharts::QChartView* chartView)
{
    if (!chartView) {
        return false;
    }

    // Проверяем и корректируем расширение файла
    QString correctedPath = ensureJpegExtension(filePath);

    // Создаем изображение с размерами графика
    QImage image(chartView->size(), QImage::Format_RGB32);
    image.fill(Qt::white); // Заполняем белым фоном

    // Рендерим график в изображение
    QPainter painter(&image);
    chartView->render(&painter);

    // Сохраняем изображение в JPEG
    return image.save(correctedPath, "JPEG");
}

QString JpegExporter::getFileFilter() const
{
    return "JPEG файл (*.jpg *.jpeg)";
}

QString JpegExporter::getFormatName() const
{
    return "JPEG";
}

QString JpegExporter::ensureJpegExtension(const QString& filePath) const
{
    if (filePath.endsWith(".jpg", Qt::CaseInsensitive) ||
        filePath.endsWith(".jpeg", Qt::CaseInsensitive)) {
        return filePath;
    }
    return filePath + ".jpg";
} 