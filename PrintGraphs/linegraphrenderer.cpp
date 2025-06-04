#include "linegraphrenderer.h"

using namespace QtCharts;

LineGraphRenderer::LineGraphRenderer(QWidget* parent)
    : BaseGraphRenderer(parent)
{
}

void LineGraphRenderer::setupSeries(const QList<QPointF>& data)
{
    // Создание новой серии данных
    QLineSeries* series = new QLineSeries();
    QPen pen(m_isColored ? Qt::blue : Qt::black, 2);
    series->setPen(pen);

    // Добавляем точки
    for (const QPointF& point : data) {
        series->append(point.x(), point.y());
    }

    // Добавление серии на график
    m_chart->addSeries(series);
}

void LineGraphRenderer::updateSeriesStyle()
{
    // Обновление стиля существующих серий
    for (QAbstractSeries* series : m_chart->series()) {
        QLineSeries* lineSeries = qobject_cast<QLineSeries*>(series);
        if (lineSeries) {
            QPen pen = lineSeries->pen();
            pen.setColor(m_isColored ? Qt::blue : Qt::black);
            lineSeries->setPen(pen);
        }
    }
} 