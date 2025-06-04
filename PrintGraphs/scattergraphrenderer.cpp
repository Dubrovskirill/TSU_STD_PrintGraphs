#include "scattergraphrenderer.h"

using namespace QtCharts;

ScatterGraphRenderer::ScatterGraphRenderer(QWidget* parent)
    : BaseGraphRenderer(parent)
{
}

void ScatterGraphRenderer::setupSeries(const QList<QPointF>& data)
{
    // Создание новой серии данных
    QScatterSeries* series = new QScatterSeries();
    series->setMarkerSize(2.0);
    series->setPen(QPen(m_isColored ? Qt::blue : Qt::black, 2));
    series->setBrush(m_isColored ? Qt::blue : Qt::black);

    // Добавляем точки
    for (const QPointF& point : data) {
        series->append(point.x(), point.y());
    }

    // Добавление серии на график
    m_chart->addSeries(series);
}

void ScatterGraphRenderer::updateSeriesStyle()
{
    // Обновление стиля существующих серий
    for (QAbstractSeries* series : m_chart->series()) {
        QScatterSeries* scatterSeries = qobject_cast<QScatterSeries*>(series);
        if (scatterSeries) {
            scatterSeries->setPen(QPen(m_isColored ? Qt::blue : Qt::black, 2));
            scatterSeries->setBrush(m_isColored ? Qt::blue : Qt::black);
        }
    }
} 