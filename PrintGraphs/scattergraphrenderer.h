#ifndef SCATTERGRAPHRENDERER_H
#define SCATTERGRAPHRENDERER_H

#include "igraphrenderer.h"
#include <QChart>
#include <QChartView>
#include <QWidget>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QDateTime>
#include <QScatterSeries>

using namespace QtCharts;

class ScatterGraphRenderer : public IGraphRenderer, public QWidget
{
public:
    explicit ScatterGraphRenderer(QWidget* parent = nullptr);
    ~ScatterGraphRenderer() override;

    // Реализация методов интерфейса IGraphRenderer
    void render(const QList<QPointF>& data) override;
    void setStyle(bool isColored) override;
    bool isEmpty() const override;
    QChartView* getChartView() const override;
    void clear() override;

private:
    QChart* m_chart;
    QChartView* m_chartView;
    bool m_isColored;
    
    // Приватные методы
    QString formatDateTime(qreal timestamp) const;
};

#endif // SCATTERGRAPHRENDERER_H 