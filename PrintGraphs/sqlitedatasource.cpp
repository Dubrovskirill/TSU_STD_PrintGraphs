#include "sqlitedatasource.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

SqliteDataSource::SqliteDataSource() : m_db(QSqlDatabase::addDatabase("QSQLITE"))
{
}

SqliteDataSource::~SqliteDataSource()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool SqliteDataSource::loadData(const QString& sourcePath)
{
    m_data.clear();
    m_error.clear();

    // Открываем базу данных
    m_db.setDatabaseName(sourcePath);
    if (!m_db.open()) {
        m_error = "Failed to open database: " + m_db.lastError().text();
        return false;
    }

    // Получаем список таблиц
    QStringList tables = m_db.tables(QSql::Tables);
    if (tables.isEmpty()) {
        m_error = "No tables found in the database";
        m_db.close();
        return false;
    }

    // Берем первую таблицу
    QString targetTable = tables.first();
    QSqlQuery pragmaQuery(m_db);
    pragmaQuery.exec("PRAGMA table_info(" + targetTable + ")");
    QStringList columnTypes;
    while (pragmaQuery.next()) {
        columnTypes.append(pragmaQuery.value("type").toString().toLower());
    }

    // Загружаем данные
    QSqlQuery query("SELECT * FROM " + targetTable, m_db);
    if (!query.exec()) {
        m_error = "Query failed: " + query.lastError().text();
        m_db.close();
        return false;
    }

    QVector<QDateTime> times;
    QVector<qreal> values;
    while (query.next()) {
        // Извлекаем данные из первого столбца (время) как строку
        QString timeStr = query.value(0).toString();

        // Парсим время в формате "dd.MM.yyyy HH:mm"
        QDateTime time = QDateTime::fromString(timeStr, "dd.MM.yyyy HH:mm");
        if (!time.isValid()) {
            m_error = "Invalid time format in first column: " + timeStr + ". Expected format: dd.MM.yyyy HH:mm";
            m_db.close();
            return false;
        }

        // Извлекаем данные из второго столбца (значение)
        bool valueOk;
        qreal value = query.value(1).toDouble(&valueOk);
        if (!valueOk) {
            m_error = "Invalid numeric value in the second column";
            m_db.close();
            return false;
        }

        // Выводим в консоль в формате x:<время> y:<значение>
        qDebug() << "x:" + timeStr + " y:" + QString::number(value);

        times.append(time);
        values.append(value);
    }

    if (times.isEmpty()) {
        m_error = "No valid data found in table " + targetTable;
        m_db.close();
        return false;
    }

    // Преобразуем время в разницу в часах от первой точки
    QDateTime baseTime = times.first();
    m_data.clear();
    for (int i = 0; i < times.size(); ++i) {
        qreal hours = baseTime.secsTo(times[i]) / 3600.0; // Разница в часах
        m_data.append(QPointF(hours, values[i]));
    }

    m_db.close();
    return true;
}

QList<QPointF> SqliteDataSource::getData() const
{
    return m_data;
}

QString SqliteDataSource::getError() const
{
    return m_error;
}
