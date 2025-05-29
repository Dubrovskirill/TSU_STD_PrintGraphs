#include "mainwindow.h"
#include "sqlitedatasource.h"
#include "jsondatasource.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_isColored(true)
{
    setupUI();
}

void MainWindow::setupUI()
{
    // Создаем центральный виджет
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Создаем главный layout
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Создаем layout для элементов управления
    QHBoxLayout* controlLayout = new QHBoxLayout();

    // Создаем комбобокс для выбора типа источника данных
    m_dataSourceCombo = new QComboBox(this);
    m_dataSourceCombo->addItem("JSON файл", "json");
    m_dataSourceCombo->addItem("SQLite база данных", "sqlite");
    controlLayout->addWidget(m_dataSourceCombo);

    // Создаем кнопку выбора файла
    m_selectFileButton = new QPushButton("Выбрать файл", this);
    controlLayout->addWidget(m_selectFileButton);

    // Создаем кнопку переключения цветного режима
    m_colorModeButton = new QPushButton("Цветной режим", this);
    m_colorModeButton->setCheckable(true);
    m_colorModeButton->setChecked(true);
    controlLayout->addWidget(m_colorModeButton);

    // Добавляем layout с элементами управления в главный layout
    mainLayout->addLayout(controlLayout);

    // Создаем и добавляем GraphRenderer
    m_graphRenderer = new GraphRenderer(this);
    mainLayout->addWidget(m_graphRenderer);

    // Подключаем сигналы к слотам
    connect(m_dataSourceCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onDataSourceTypeChanged);
    connect(m_selectFileButton, &QPushButton::clicked,
            this, &MainWindow::onSelectFileClicked);
    connect(m_colorModeButton, &QPushButton::toggled,
            this, &MainWindow::onColorModeChanged);

    // Устанавливаем минимальный размер окна
    resize(800, 600);
    setWindowTitle("Графики данных");
}

void MainWindow::onDataSourceTypeChanged(int index)
{
    // Сбрасываем текущий файл при смене типа источника
    m_currentFilePath.clear();
    m_selectFileButton->setEnabled(true);
}

void MainWindow::onSelectFileClicked()
{
    QString fileType = m_dataSourceCombo->currentData().toString();
    QString filter;
    if (fileType == "json") {
        filter = "JSON файлы (*.json)";
    } else {
        filter = "SQLite базы данных (*.sqlite)";
    }

    QString filePath = QFileDialog::getOpenFileName(this,
        "Выберите файл данных",
        "InputData",
        filter);

    if (!filePath.isEmpty()) {
        m_currentFilePath = filePath;
        loadData(filePath);
    }
}

void MainWindow::onColorModeChanged(bool checked)
{
    m_isColored = checked;
    m_colorModeButton->setText(checked ? "Цветной режим" : "Монохромный режим");
    m_graphRenderer->setStyle(checked);
}

void MainWindow::loadData(const QString& filePath)
{
    QString fileType = m_dataSourceCombo->currentData().toString();
    std::unique_ptr<IDataSource> dataSource;

    if (fileType == "json") {
        dataSource = std::make_unique<JsonDataSource>();
    } else {
        dataSource = std::make_unique<SqliteDataSource>();
    }

    if (!dataSource->loadData(filePath)) {
        QMessageBox::critical(this, "Ошибка",
            "Не удалось загрузить данные: " + dataSource->getError());
        return;
    }

    m_graphRenderer->render(dataSource->getData());
} 