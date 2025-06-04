#ifndef SCATTERGRAPHRENDERER_H
#define SCATTERGRAPHRENDERER_H

#include "basegraphrenderer.h"
#include <QScatterSeries>

using namespace QtCharts;

class ScatterGraphRenderer : public BaseGraphRenderer
{
public:
    explicit ScatterGraphRenderer(QWidget* parent = nullptr);
    ~ScatterGraphRenderer() override = default;

protected:
    // Реализация абстрактных методов базового класса
    void setupSeries(const QList<QPointF>& data) override;
    void updateSeriesStyle() override;
};

#endif // SCATTERGRAPHRENDERER_H 