#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Создаем центральный виджет
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Создаем layout для центрального виджета
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    // Создаем и добавляем GraphRenderer
    m_graphRenderer = new GraphRenderer(this);
    layout->addWidget(m_graphRenderer);

    // Устанавливаем минимальный размер окна
    resize(800, 600);
    setWindowTitle("Графики данных");
} 