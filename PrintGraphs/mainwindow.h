#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QListWidget>
#include <QStatusBar>
#include "graphrenderer.h"
#include "datasource.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void onSelectDirectoryClicked();
    void onFileSelectedFromList(QListWidgetItem* item);
    void onColorModeChanged(bool checked);

private:
    void setupUI();
    void listFilesInDirectory(const QString& directoryPath);
    void loadData(const QString& filePath);
    void updateStatus(const QString& message, int timeout = 0);

    GraphRenderer* m_graphRenderer;    // Виджет для отображения графика
    QPushButton* m_selectDirectoryButton;   // Кнопка выбора папки
    QListWidget* m_fileListWidget;       // Список файлов
    QPushButton* m_colorModeButton;    // Кнопка переключения цветного/монохромного режима
    QStatusBar* m_statusBar;         // Строка состояния
    
    QString m_currentDirectoryPath;    // Текущий выбранный каталог
    bool m_isColored;                  // Флаг цветного режима
};

#endif // MAINWINDOW_H 