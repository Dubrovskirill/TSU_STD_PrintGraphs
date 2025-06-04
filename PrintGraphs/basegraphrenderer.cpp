#include "basegraphrenderer.h"
#include <QVBoxLayout>
#include <limits>

using namespace QtCharts;

BaseGraphRenderer::BaseGraphRenderer(QWidget* parent)
    : QWidget(parent)
    , m_chart(new QChart())
    , m_chartView(new QChartView(m_chart, this))
    , m_isColored(true)
{
    // Настройка QChartView
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setMinimumSize(400, 300);

    // Настройка layout для отображения графика
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_chartView);
    setLayout(layout);

    // Начальная настройка графика
    m_chart->setTitle("Data Visualization");
    m_chart->legend()->hide();
}

BaseGraphRenderer::~BaseGraphRenderer()
{
    // QChart и QChartView автоматически очищаются через родительский QWidget
}

QString BaseGraphRenderer::formatDateTime(qreal timestamp) const
{
    QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(timestamp));
    return dateTime.toString("dd.MM.yyyy HH:mm");
}

void BaseGraphRenderer::render(const QList<QPointF>& data)
{
    // Очистка предыдущих данных
    m_chart->removeAllSeries();
    
    // Удаляем старые оси
    for (auto* axis : m_chart->axes()) {
        m_chart->removeAxis(axis);
        delete axis;
    }

    // Настройка серий данных (реализуется в наследниках)
    setupSeries(data);

    // Настройка осей
    setupAxes(data);
}

void BaseGraphRenderer::setStyle(bool isColored)
{
    m_isColored = isColored;
    updateSeriesStyle();
}

bool BaseGraphRenderer::isEmpty() const
{
    return m_chart ? m_chart->series().isEmpty() : true;
}

QChartView* BaseGraphRenderer::getChartView() const
{
    return m_chartView;
}

void BaseGraphRenderer::clear()
{
    // Удаляем все серии данных
    m_chart->removeAllSeries();
    
    // Удаляем все оси
    for (auto* axis : m_chart->axes()) {
        m_chart->removeAxis(axis);
        delete axis;
    }

    // Сбрасываем заголовок и легенду
    m_chart->setTitle("");
    m_chart->legend()->hide();
}

void BaseGraphRenderer::setupAxes(const QList<QPointF>& data)
{
    // Настройка осей
    QDateTimeAxis* axisX = new QDateTimeAxis();
    axisX->setTitleText("Date/Time");
    axisX->setFormat("dd.MM.yyyy HH:mm");

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Value");
    axisY->setLabelFormat("%.1f");

    // Расчет диапазонов осей
    qreal minX, maxX, minY, maxY;
    calculateAxisRanges(data, minX, maxX, minY, maxY);

    // Устанавливаем диапазон для оси X в миллисекундах
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(minX)),
                   QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(maxX)));
    axisY->setRange(minY, maxY);

    // Добавление осей на график
    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignLeft);

    // Привязка осей к сериям
    for (QAbstractSeries* series : m_chart->series()) {
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }
}

void BaseGraphRenderer::calculateAxisRanges(const QList<QPointF>& data,
                                          qreal& minX, qreal& maxX,
                                          qreal& minY, qreal& maxY)
{
    minX = std::numeric_limits<qreal>::max();
    maxX = std::numeric_limits<qreal>::min();
    minY = std::numeric_limits<qreal>::max();
    maxY = std::numeric_limits<qreal>::min();

    for (const QPointF& point : data) {
        minX = qMin(minX, point.x());
        maxX = qMax(maxX, point.x());
        minY = qMin(minY, point.y());
        maxY = qMax(maxY, point.y());
    }
} 