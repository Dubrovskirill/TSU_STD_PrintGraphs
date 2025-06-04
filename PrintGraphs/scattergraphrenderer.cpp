#include "scattergraphrenderer.h"
#include <QVBoxLayout>

using namespace QtCharts;

ScatterGraphRenderer::ScatterGraphRenderer(QWidget* parent)
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

ScatterGraphRenderer::~ScatterGraphRenderer()
{
    // QChart и QChartView автоматически очищаются через родительский QWidget
}

QString ScatterGraphRenderer::formatDateTime(qreal timestamp) const
{
    QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(timestamp));
    return dateTime.toString("dd.MM.yyyy HH:mm");
}

void ScatterGraphRenderer::render(const QList<QPointF>& data)
{
    // Очистка предыдущих данных
    m_chart->removeAllSeries();
    
    // Удаляем старые оси
    for (auto* axis : m_chart->axes()) {
        m_chart->removeAxis(axis);
        delete axis;
    }

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

    // Настройка осей
    QDateTimeAxis* axisX = new QDateTimeAxis();
    axisX->setTitleText("Date/Time");
    axisX->setFormat("dd.MM.yyyy HH:mm");

    QValueAxis* axisY = new QValueAxis();
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

    // Устанавливаем диапазон для оси X в миллисекундах
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(minX)),
                   QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(maxX)));
    axisY->setRange(minY, maxY);

    // Добавление осей на график и привязка к серии
    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
}

void ScatterGraphRenderer::setStyle(bool isColored)
{
    m_isColored = isColored;

    // Обновление стиля существующих серий
    for (QAbstractSeries* series : m_chart->series()) {
        QScatterSeries* scatterSeries = qobject_cast<QScatterSeries*>(series);
        if (scatterSeries) {
            scatterSeries->setPen(QPen(isColored ? Qt::blue : Qt::black, 2));
            scatterSeries->setBrush(isColored ? Qt::blue : Qt::black);
        }
    }
}

void ScatterGraphRenderer::clear()
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

bool ScatterGraphRenderer::isEmpty() const
{
    return m_chart ? m_chart->series().isEmpty() : true;
}

QChartView* ScatterGraphRenderer::getChartView() const
{
    return m_chartView;
} 
