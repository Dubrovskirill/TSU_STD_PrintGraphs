#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QListWidget>
#include <QComboBox>
#include <QStatusBar>
#include <QtGui/qpdfwriter.h>
#include "graphrenderer.h"
#include "datasource.h"
#include "exporterfactory.h"

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
    void onPrintButtonClicked();
    void onExportFormatChanged(int index);

private:
    void setupUI();
    void listFilesInDirectory(const QString& directoryPath);
    void loadData(const QString& filePath);
    void showError(const QString& message);

    GraphRenderer* m_graphRenderer;    // Виджет для отображения графика
    QPushButton* m_selectDirectoryButton;   // Кнопка выбора папки
    QListWidget* m_fileListWidget;       // Список файлов
    QPushButton* m_colorModeButton;    // Кнопка переключения цветного/монохромного режима
    QPushButton* m_printButton;        // Кнопка печати в PDF
    QComboBox* m_exportFormatCombo;    // Выпадающий список форматов экспорта
    
    QString m_currentDirectoryPath;    // Текущий выбранный каталог
    bool m_isColored;                  // Флаг цветного режима
};

#endif // MAINWINDOW_H 