#include "graphrenderer.h"
#include <QLineSeries>
#include <QValueAxis>
#include <QVBoxLayout> // Добавлен для QVBoxLayout
#include <QApplication>

GraphRenderer::GraphRenderer(QWidget* parent)
    : QWidget(parent)
    , m_chart(new QtCharts::QChart())
    , m_chartView(new QtCharts::QChartView(m_chart, this))
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

GraphRenderer::~GraphRenderer()
{
    // QChart и QChartView автоматически очищаются через родительский QWidget
}

void GraphRenderer::render(const QList<QPointF>& data)
{
    // Очистка предыдущих данных
    m_chart->removeAllSeries();
    
    // Удаляем старые оси
    for (auto* axis : m_chart->axes()) {
        m_chart->removeAxis(axis);
        delete axis;
    }

    // Создание новой серии данных
    QtCharts::QLineSeries* series = new QtCharts::QLineSeries();
    series->append(data);

    // Настройка стиля линии
    QPen pen = series->pen();
    pen.setWidth(2);
    pen.setColor(m_isColored ? Qt::blue : Qt::black);
    series->setPen(pen);

    // Добавление серии на график
    m_chart->addSeries(series);

    // Настройка осей
    QtCharts::QValueAxis* axisX = new QtCharts::QValueAxis();
    axisX->setTitleText("Time (hours)");
    axisX->setLabelFormat("%.1f");

    QtCharts::QValueAxis* axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("Value");
    axisY->setLabelFormat("%.1f");

    // Автоматическая настройка диапазона осей
    qreal minX = std::numeric_limits<qreal>::max();
    qreal maxX = std::numeric_limits<qreal>::min();
    qreal minY = std::numeric_limits<qreal>::max();
    qreal maxY = std::numeric_limits<qreal>::min();

    for (const QPointF& point : data) {
        minX = qMin(minX, point.x());
        maxX = qMax(maxX, point.x());
        minY = qMin(minY, point.y());
        maxY = qMax(maxY, point.y());
    }

    axisX->setRange(minX, maxX);
    axisY->setRange(minY, maxY);

    // Добавление осей на график и привязка к серии
    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
}

void GraphRenderer::setStyle(bool isColored)
{
    m_isColored = isColored;

    // Обновление стиля существующих серий
    for (QtCharts::QAbstractSeries* series : m_chart->series()) {
        QtCharts::QLineSeries* lineSeries = qobject_cast<QtCharts::QLineSeries*>(series);
        if (lineSeries) {
            QPen pen = lineSeries->pen();
            pen.setColor(isColored ? Qt::blue : Qt::black);
            lineSeries->setPen(pen);
        }
    }
}

bool GraphRenderer::isEmpty() const
{
    return m_chart->series().isEmpty();
}

void GraphRenderer::clear()
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
