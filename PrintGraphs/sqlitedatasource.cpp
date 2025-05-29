#include "sqlitedatasource.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QDateTime>
#include <QStringList>
#include <QDate>
#include <QTime>

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

    while (query.next()) {
        // Извлекаем данные из первого столбца (время) как строку
        QString timeStr = query.value(0).toString();
        QDateTime time;

        // Попытка парсинга в формате "dd.MM.yyyy HH:mm"
        time = QDateTime::fromString(timeStr, "dd.MM.yyyy HH:mm");

        // Если не удалось, попытка парсинга в формате "dd.MM.yyyy <минуты от начала дня>"
        if (!time.isValid()) {
            QStringList parts = timeStr.split(' ');
            if (parts.size() == 2) {
                QDate date = QDate::fromString(parts[0], "dd.MM.yyyy");
                bool ok;
                int totalMinutes = parts[1].toInt(&ok);

                if (date.isValid() && ok) {
                    // Если минуты >= 1440 (24 часа), считаем это 00:00 следующего дня
                    if (totalMinutes >= 1440) {
                        date = date.addDays(totalMinutes / 1440);
                        totalMinutes = totalMinutes % 1440; // Оставшиеся минуты для нового дня
                    }
                    
                    int hours = totalMinutes / 60;
                    int remainingMinutes = totalMinutes % 60;
                    QTime qtime(hours, remainingMinutes);
                    
                    if (qtime.isValid()) {
                        time = QDateTime(date, qtime);
                    }
                }
            }
        }
        
        // Устанавливаем временную зону UTC, чтобы избежать проблем с локальным временем
        time.setTimeSpec(Qt::UTC);

        if (!time.isValid()) {
            m_error = "Invalid time format in first column: " + timeStr + ". Expected formats: dd.MM.yyyy HH:mm or dd.MM.yyyy <total minutes from start of day>";
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

        // Конвертируем время в миллисекунды с начала эпохи для оси времени
        m_data.append(QPointF(time.toMSecsSinceEpoch(), value));
    }

    if (m_data.isEmpty()) { // Проверяем m_data напрямую
        m_error = "No valid data found in table " + targetTable;
        m_db.close();
        return false;
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
