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
#include <QPdfWriter>
#include <QPainter>
#include <QStatusBar>

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

    // Создаем кнопку печати в PDF
    m_printButton = new QPushButton("Сохранить в PDF", this);
    m_printButton->setEnabled(false); // По умолчанию кнопка неактивна
    controlLayout->addWidget(m_printButton);

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

    // Создаем статус бар
    statusBar()->showMessage("Готов к работе");

    // Подключаем сигналы к слотам
    connect(m_selectDirectoryButton, &QPushButton::clicked,
            this, &MainWindow::onSelectDirectoryClicked);
    connect(m_fileListWidget, &QListWidget::itemDoubleClicked,
            this, &MainWindow::onFileSelectedFromList);
    connect(m_colorModeButton, &QPushButton::toggled,
            this, &MainWindow::onColorModeChanged);
    connect(m_printButton, &QPushButton::clicked,
            this, &MainWindow::onPrintButtonClicked);

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
        statusBar()->showMessage("Папка успешно выбрана", 3000);
    } else {
        statusBar()->showMessage("Выбор папки отменен", 3000);
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
    statusBar()->showMessage(checked ? "Установлен цветной режим" : "Установлен монохромный режим", 3000);
}

void MainWindow::loadData(const QString& filePath)
{
    QSharedPointer<IDataSource> dataSource = DataSourceFactory::createSource(filePath);

    if (!dataSource) {
         QMessageBox::critical(this, "Ошибка", "Неподдерживаемый формат файла: " + filePath);
         statusBar()->showMessage("Ошибка: неподдерживаемый формат файла", 3000);
         m_printButton->setEnabled(false);
         return;
    }

    if (!dataSource->loadData(filePath)) {
        QMessageBox::critical(this, "Ошибка",
            "Не удалось загрузить данные: " + dataSource->getError());
        statusBar()->showMessage("Ошибка загрузки данных", 3000);
        m_printButton->setEnabled(false);
        return;
    }

    m_graphRenderer->render(dataSource->getData());
    m_printButton->setEnabled(true);
    statusBar()->showMessage("Данные успешно загружены", 3000);
}

void MainWindow::onPrintButtonClicked()
{
    if (m_graphRenderer->isEmpty()) {
        showError("Нельзя напечатать пустой график...");
        statusBar()->showMessage("Ошибка: график пуст", 3000);
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this, "Сохранить график", "", "PDF (*.pdf)");
    if (!filePath.isEmpty()) {
        QPdfWriter pdfWriter(filePath);
        QPainter painter(&pdfWriter);
        m_graphRenderer->getChartView()->render(&painter);
        statusBar()->showMessage("График успешно сохранен в PDF", 3000);
    } else {
        statusBar()->showMessage("Сохранение отменено", 3000);
    }
}

void MainWindow::showError(const QString& message)
{
    QMessageBox::critical(this, "Ошибка", message);
} 