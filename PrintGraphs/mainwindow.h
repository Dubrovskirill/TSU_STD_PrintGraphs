#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QFileDialog>
#include "graphrenderer.h"
#include "datasource.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void onDataSourceTypeChanged(int index);
    void onSelectFileClicked();
    void onColorModeChanged(bool checked);

private:
    void setupUI();
    void loadData(const QString& filePath);

    GraphRenderer* m_graphRenderer;    // Виджет для отображения графика
    QComboBox* m_dataSourceCombo;      // Выбор типа источника данных
    QPushButton* m_selectFileButton;   // Кнопка выбора файла
    QPushButton* m_colorModeButton;    // Кнопка переключения цветного/монохромного режима
    
    QString m_currentFilePath;         // Текущий выбранный файл
    bool m_isColored;                  // Флаг цветного режима
};

#endif // MAINWINDOW_H 