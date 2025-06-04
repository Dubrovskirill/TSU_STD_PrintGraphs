#ifndef LINEGRAPHRENDERER_H
#define LINEGRAPHRENDERER_H

#include "basegraphrenderer.h"
#include <QLineSeries>

using namespace QtCharts;

class LineGraphRenderer : public BaseGraphRenderer
{
public:
    explicit LineGraphRenderer(QWidget* parent = nullptr);
    ~LineGraphRenderer() override = default;

protected:
    // Реализация абстрактных методов базового класса
    void setupSeries(const QList<QPointF>& data) override;
    void updateSeriesStyle() override;
};

#endif // LINEGRAPHRENDERER_H
