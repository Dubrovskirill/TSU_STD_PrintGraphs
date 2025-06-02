#include "areagraphrenderer.h"
#include <QAreaSeries>
#include <QLineSeries>
#include <QValueAxis>
#include <QVBoxLayout>
#include <QApplication>

AreaGraphRenderer::AreaGraphRenderer(QWidget* parent)
    : QWidget(parent)
    , m_chart(new QtCharts::QChart())
    , m_chartView(new QtCharts::QChartView(m_chart, this))
    , m_isColored(true)
{
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setMinimumSize(400, 300);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_chartView);
    setLayout(layout);

    m_chart->setTitle("Data Visualization");
    m_chart->legend()->hide();
}

AreaGraphRenderer::~AreaGraphRenderer()
{
}

void AreaGraphRenderer::render(const QList<QPointF>& data)
{
    m_chart->removeAllSeries();
    
    for (auto* axis : m_chart->axes()) {
        m_chart->removeAxis(axis);
        delete axis;
    }

    // Создаем верхнюю линию
    QtCharts::QLineSeries* upperSeries = new QtCharts::QLineSeries();
    upperSeries->append(data);

    // Создаем нижнюю линию (все точки с y = 0)
    QtCharts::QLineSeries* lowerSeries = new QtCharts::QLineSeries();
    for (const QPointF& point : data) {
        lowerSeries->append(QPointF(point.x(), 0));
    }

    // Создаем область между линиями
    QtCharts::QAreaSeries* areaSeries = new QtCharts::QAreaSeries(upperSeries, lowerSeries);
    
    // Настраиваем стиль области
    QPen pen = areaSeries->pen();
    pen.setWidth(2);
    pen.setColor(m_isColored ? Qt::blue : Qt::black);
    areaSeries->setPen(pen);

    // Настраиваем заливку области
    QColor areaColor = m_isColored ? QColor(0, 0, 255, 0) : QColor(0, 0, 0, 50);
    areaSeries->setBrush(areaColor);

    m_chart->addSeries(areaSeries);

    // Настройка осей
    QtCharts::QDateTimeAxis* axisX = new QtCharts::QDateTimeAxis();
    axisX->setTitleText("Time");
    axisX->setFormat("dd.MM.yyyy HH:mm");

    QtCharts::QValueAxis* axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("Value");
    axisY->setLabelFormat("%.1f");

    // Находим минимальные и максимальные значения
    qreal minX = std::numeric_limits<qreal>::max();
    qreal maxX = std::numeric_limits<qreal>::min();
    qreal minY = 0; // Для area chart минимум всегда 0
    qreal maxY = std::numeric_limits<qreal>::min();

    for (const QPointF& point : data) {
        minX = qMin(minX, point.x());
        maxX = qMax(maxX, point.x());
        maxY = qMax(maxY, point.y());
    }

    // Устанавливаем диапазоны осей
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(minX), QDateTime::fromMSecsSinceEpoch(maxX));
    axisY->setRange(minY, maxY);

    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    areaSeries->attachAxis(axisX);
    areaSeries->attachAxis(axisY);
}

void AreaGraphRenderer::setStyle(bool isColored)
{
    m_isColored = isColored;

    for (QtCharts::QAbstractSeries* series : m_chart->series()) {
        QtCharts::QAreaSeries* areaSeries = qobject_cast<QtCharts::QAreaSeries*>(series);
        if (areaSeries) {
            QPen pen = areaSeries->pen();
            pen.setColor(isColored ? Qt::blue : Qt::black);
            areaSeries->setPen(pen);
            
            QColor areaColor = isColored ? QColor(0, 0, 255, 50) : QColor(0, 0, 0, 50);
            areaSeries->setBrush(areaColor);
        }
    }
}

bool AreaGraphRenderer::isEmpty() const
{
    return m_chart->series().isEmpty();
}

void AreaGraphRenderer::clear()
{
    m_chart->removeAllSeries();
    for (auto* axis : m_chart->axes()) {
        m_chart->removeAxis(axis);
        delete axis;
    }
    m_chart->setTitle("Data Visualization");
    m_chart->legend()->hide();
}

QString AreaGraphRenderer::formatDateTime(qreal timestamp) const
{
    return QDateTime::fromMSecsSinceEpoch(timestamp).toString("dd.MM.yyyy HH:mm");
} 
