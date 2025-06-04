#ifndef BASEGRAPHRENDERER_H
#define BASEGRAPHRENDERER_H

#include "igraphrenderer.h"
#include <QChart>
#include <QChartView>
#include <QWidget>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QDateTime>
#include <QVBoxLayout>

using namespace QtCharts;

class BaseGraphRenderer : public IGraphRenderer, public QWidget
{
public:
    explicit BaseGraphRenderer(QWidget* parent = nullptr);
    virtual ~BaseGraphRenderer() override;

    // Реализация методов интерфейса IGraphRenderer
    void render(const QList<QPointF>& data) override;
    void setStyle(bool isColored) override;
    bool isEmpty() const override;
    QChartView* getChartView() const override;
    void clear() override;

protected:
    // Защищенные методы для переопределения в наследниках
    virtual void setupSeries(const QList<QPointF>& data) = 0;
    virtual void updateSeriesStyle() = 0;

    // Вспомогательные методы
    QString formatDateTime(qreal timestamp) const;
    void setupAxes(const QList<QPointF>& data);
    void calculateAxisRanges(const QList<QPointF>& data, 
                           qreal& minX, qreal& maxX, 
                           qreal& minY, qreal& maxY);

    // Общие члены класса
    QChart* m_chart;
    QChartView* m_chartView;
    bool m_isColored;
};

#endif // BASEGRAPHRENDERER_H 