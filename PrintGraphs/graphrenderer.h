#ifndef GRAPHRENDERER_H
#define GRAPHRENDERER_H

#include "igraphrenderer.h"
#include <QChart>
#include <QChartView>
#include <QWidget>

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

private:
    QtCharts::QChart* m_chart; // График
    QtCharts::QChartView* m_chartView; // Представление графика
    bool m_isColored; // Флаг текущего стиля
};

#endif // GRAPHRENDERER_H
