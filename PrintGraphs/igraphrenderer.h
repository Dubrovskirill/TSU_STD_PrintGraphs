#ifndef GRAPHRENDERE_H
#define GRAPHRENDERE_H

#include <QList>
#include <QPointF>
#include <QtCharts/QChartView>

// Интерфейс для рендеринга графиков
class IGraphRenderer
{
public:
    virtual ~IGraphRenderer() = default;
    
    // Основные методы рендеринга
    virtual void render(const QList<QPointF>& data) = 0;
    virtual void setStyle(bool isColored) = 0;
    
    // Методы управления состоянием
    virtual void clear() = 0;
    virtual bool isEmpty() const = 0;
    
    // Метод для получения представления графика
    virtual QtCharts::QChartView* getChartView() const = 0;
};

#endif // GRAPHRENDERE_H
