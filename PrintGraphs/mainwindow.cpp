#include "mainwindow.h"
#include "sqlitedatasource.h"
#include "jsondatasource.h"
#include "datasourcefactory.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QDir>
#include <QSplitter>

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

    // Создаем главный вертикальный layout
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Создаем горизонтальный layout для элементов управления
    QHBoxLayout* controlLayout = new QHBoxLayout();

    // Создаем кнопку выбора папки
    m_selectDirectoryButton = new QPushButton("Выбрать папку с данными", this);
    controlLayout->addWidget(m_selectDirectoryButton);

    // Создаем кнопку переключения цветного режима
    m_colorModeButton = new QPushButton("Цветной режим", this);
    m_colorModeButton->setCheckable(true);
    m_colorModeButton->setChecked(true);
    controlLayout->addWidget(m_colorModeButton);

    // Добавляем layout с элементами управления в главный layout
    mainLayout->addLayout(controlLayout);

    // Создаем QSplitter для списка файлов и графика
    QSplitter* dataSplitter = new QSplitter(Qt::Horizontal, this);

    // Создаем и добавляем список файлов в сплиттер
    m_fileListWidget = new QListWidget(this);
    dataSplitter->addWidget(m_fileListWidget);

    // Создаем и добавляем GraphRenderer в сплиттер
    m_graphRenderer = new GraphRenderer(this);
    dataSplitter->addWidget(m_graphRenderer);

    // Добавляем сплиттер в главный layout
    mainLayout->addWidget(dataSplitter);

    // Подключаем сигналы к слотам
    connect(m_selectDirectoryButton, &QPushButton::clicked,
            this, &MainWindow::onSelectDirectoryClicked);
    connect(m_fileListWidget, &QListWidget::itemDoubleClicked,
            this, &MainWindow::onFileSelectedFromList);
    connect(m_colorModeButton, &QPushButton::toggled,
            this, &MainWindow::onColorModeChanged);

    // Устанавливаем минимальный размер окна
    resize(1000, 600);
    setWindowTitle("Графики данных");
}

void MainWindow::onSelectDirectoryClicked()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this,
        "Выберите папку с данными",
        "InputData");

    if (!directoryPath.isEmpty()) {
        m_currentDirectoryPath = directoryPath;
        listFilesInDirectory(directoryPath);
    }
}

void MainWindow::listFilesInDirectory(const QString& directoryPath)
{
    m_fileListWidget->clear();
    QDir directory(directoryPath);
    QStringList fileList = directory.entryList(QDir::Files | QDir::NoDotAndDotDot);

    for (const QString& fileName : fileList) {
        m_fileListWidget->addItem(fileName);
    }
}

void MainWindow::onFileSelectedFromList(QListWidgetItem* item)
{
    QString fileName = item->text();
    QString filePath = m_currentDirectoryPath + "/" + fileName;
    loadData(filePath);
}

void MainWindow::onColorModeChanged(bool checked)
{
    m_isColored = checked;
    m_colorModeButton->setText(checked ? "Цветной режим" : "Монохромный режим");
    m_graphRenderer->setStyle(checked);
}

void MainWindow::loadData(const QString& filePath)
{
    QSharedPointer<IDataSource> dataSource = DataSourceFactory::createSource(filePath);

    if (!dataSource) {
         QMessageBox::critical(this, "Ошибка", "Неподдерживаемый формат файла: " + filePath);
         return;
    }

    if (!dataSource->loadData(filePath)) {
        QMessageBox::critical(this, "Ошибка",
            "Не удалось загрузить данные: " + dataSource->getError());
        return;
    }

    m_graphRenderer->render(dataSource->getData());
} 