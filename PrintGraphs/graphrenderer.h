#ifndef GRAPHRENDERER_H
#define GRAPHRENDERER_H

#include "igraphrenderer.h"
#include <QChart>
#include <QChartView>
#include <QWidget>
#include <QDateTimeAxis>

// Реализация интерфейса IGraphRenderer с использованием Qt Charts
class GraphRenderer : public IGraphRenderer, public QWidget
{
public:
    explicit GraphRenderer(QWidget* parent = nullptr);
    ~GraphRenderer() override;

    // Реализация метода рендеринга графика
    void render(const QList<QPointF>& data) override;

    // Установка стиля (цветной или монохромный)
    void setStyle(bool isColored) override;

    // Проверка, пуст ли график
    bool isEmpty() const;

    // Получение указателя на QChartView
    QtCharts::QChartView* getChartView() const { return m_chartView; }

    // Очистка графика
    void clear();

private:
    QtCharts::QChart* m_chart; // График
    QtCharts::QChartView* m_chartView; // Представление графика
    bool m_isColored; // Флаг текущего стиля

    // Вместо QValueAxis для оси X будем использовать QDateTimeAxis
    // QtCharts::QValueAxis* m_axisX; // Больше не нужен
    // QtCharts::QValueAxis* m_axisY; // Ось Y остается QValueAxis
};

#endif // GRAPHRENDERER_H
