#ifndef GRAPHRENDERE_H
#define GRAPHRENDERE_H

#include <QList>
#include <QPointF>

// Интерфейс для рендеринга графиков
class IGraphRenderer
{
public:
    virtual ~IGraphRenderer() = default;
    virtual void render(const QList<QPointF>& data) = 0;
    virtual void setStyle(bool isColored) = 0;
};

#endif // GRAPHRENDERE_H
