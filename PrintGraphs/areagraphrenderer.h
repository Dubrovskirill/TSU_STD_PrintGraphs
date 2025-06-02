#ifndef AREAGRAPHRENDERER_H
#define AREAGRAPHRENDERER_H

#include "igraphrenderer.h"
#include <QChart>
#include <QChartView>
#include <QWidget>
#include <QDateTimeAxis>
#include <QDateTime>

class AreaGraphRenderer : public IGraphRenderer, public QWidget
{
public:
    explicit AreaGraphRenderer(QWidget* parent = nullptr);
    ~AreaGraphRenderer() override;

    void render(const QList<QPointF>& data) override;
    void setStyle(bool isColored) override;
    bool isEmpty() const;
    QtCharts::QChartView* getChartView() const { return m_chartView; }
    void clear();

private:
    QtCharts::QChart* m_chart;
    QtCharts::QChartView* m_chartView;
    bool m_isColored;
    QString formatDateTime(qreal timestamp) const;
};

#endif // AREAGRAPHRENDERER_H 