#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphrenderer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private:
    GraphRenderer* m_graphRenderer; // Виджет для отображения графика
};

#endif // MAINWINDOW_H 