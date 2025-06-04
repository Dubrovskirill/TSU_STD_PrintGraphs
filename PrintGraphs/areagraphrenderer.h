#ifndef AREAGRAPHRENDERER_H
#define AREAGRAPHRENDERER_H

#include "basegraphrenderer.h"
#include <QAreaSeries>
#include <QLineSeries>

using namespace QtCharts;

class AreaGraphRenderer : public BaseGraphRenderer
{
public:
    explicit AreaGraphRenderer(QWidget* parent = nullptr);
    ~AreaGraphRenderer() override = default;

protected:
    // Реализация абстрактных методов базового класса
    void setupSeries(const QList<QPointF>& data) override;
    void updateSeriesStyle() override;
};

#endif // AREAGRAPHRENDERER_H 