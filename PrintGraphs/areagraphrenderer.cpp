#include "areagraphrenderer.h"

using namespace QtCharts;

AreaGraphRenderer::AreaGraphRenderer(QWidget* parent)
    : BaseGraphRenderer(parent)
{
}

void AreaGraphRenderer::setupSeries(const QList<QPointF>& data)
{
    // Создаем верхнюю серию (с данными)
    QLineSeries* upperSeries = new QLineSeries();
    QPen pen(m_isColored ? Qt::blue : Qt::black, 2);
    upperSeries->setPen(pen);

    // Создаем нижнюю серию (с нулевыми значениями)
    QLineSeries* lowerSeries = new QLineSeries();
    lowerSeries->setPen(QPen(Qt::transparent)); // Делаем линию невидимой

    // Добавляем точки
    for (const QPointF& point : data) {
        upperSeries->append(point.x(), point.y());
        lowerSeries->append(point.x(), 0);
    }

    // Создаем серию области
    QAreaSeries* areaSeries = new QAreaSeries(upperSeries, lowerSeries);
    areaSeries->setPen(QPen(m_isColored ? Qt::blue : Qt::black, 2));
    areaSeries->setBrush(m_isColored ? QColor(0, 0, 255, 50) : QColor(0, 0, 0, 50));

    // Добавление серии на график
    m_chart->addSeries(areaSeries);
}

void AreaGraphRenderer::updateSeriesStyle()
{
    // Обновление стиля существующих серий
    for (QAbstractSeries* series : m_chart->series()) {
        QAreaSeries* areaSeries = qobject_cast<QAreaSeries*>(series);
        if (areaSeries) {
            // Обновляем стиль области
            areaSeries->setPen(QPen(m_isColored ? Qt::blue : Qt::black, 2));
            areaSeries->setBrush(m_isColored ? QColor(0, 0, 255, 50) : QColor(0, 0, 0, 50));

            // Обновляем стиль верхней линии
            if (QLineSeries* upperSeries = qobject_cast<QLineSeries*>(areaSeries->upperSeries())) {
                upperSeries->setPen(QPen(m_isColored ? Qt::blue : Qt::black, 2));
            }
        }
    }
} 