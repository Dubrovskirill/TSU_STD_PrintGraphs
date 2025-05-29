#include "jsondatasource.h"
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QDate>
#include <QTime>

bool JsonDataSource::loadData(const QString& sourcePath)
{
    m_data.clear();
    m_error.clear();

    // Открываем файл
    QFile file(sourcePath);
    if (!file.open(QIODevice::ReadOnly)) {
        m_error = "Failed to open file: " + file.errorString();
        return false;
    }

    // Читаем JSON
    QByteArray jsonData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    
    if (doc.isNull()) {
        m_error = "Invalid JSON format";
        return false;
    }

    if (!doc.isArray()) {
        m_error = "JSON root must be an array";
        return false;
    }

    QJsonArray array = doc.array();
    if (!validateJsonFormat(array)) {
        return false;
    }

    for (const QJsonValue& value : array) {
        if (!value.isArray() || value.toArray().size() != 2) {
            m_error = "Each array element must be an array with exactly 2 elements";
            return false;
        }

        QJsonArray pointArray = value.toArray();
        QString dateTimeStr = pointArray[0].toString();
        QDateTime dateTime;
        
        if (!parseDateTime(dateTimeStr, dateTime)) {
            return false;
        }

        // Проверяем, что значение является числом
        if (!pointArray[1].isDouble()) {
            m_error = "Invalid numeric value in JSON";
            return false;
        }

        qreal pointValue = pointArray[1].toDouble();

        // Конвертируем время в миллисекунды с начала эпохи для оси времени
        m_data.append(QPointF(dateTime.toMSecsSinceEpoch(), pointValue));
    }

    return true;
}

QList<QPointF> JsonDataSource::getData() const
{
    return m_data;
}

QString JsonDataSource::getError() const
{
    return m_error;
}

bool JsonDataSource::validateJsonFormat(const QJsonArray& array)
{
    for (const QJsonValue& value : array) {
        if (!value.isArray()) {
            m_error = "Each array element must be an array";
            return false;
        }

        QJsonArray pointArray = value.toArray();
        if (pointArray.size() != 2) {
            m_error = "Each point array must contain exactly 2 elements";
            return false;
        }

        if (!pointArray[0].isString()) {
            m_error = "First element must be a date string";
            return false;
        }

        if (!pointArray[1].isDouble()) {
            m_error = "Second element must be a number";
            return false;
        }
    }
    return true;
}

bool JsonDataSource::parseDateTime(const QString& dateTimeStr, QDateTime& dateTime)
{
    // Попытка парсинга в формате "dd.MM.yyyy HH:mm"
    dateTime = QDateTime::fromString(dateTimeStr, "dd.MM.yyyy HH:mm");

    // Если не удалось, попытка парсинга в формате "dd.MM.yyyy <минуты от начала дня>"
    if (!dateTime.isValid()) {
        QStringList parts = dateTimeStr.split(' ');
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
                QTime time(hours, remainingMinutes);
                
                if (time.isValid()) {
                    dateTime = QDateTime(date, time);
                }
            }
        }
    }
    
    // Устанавливаем временную зону UTC, чтобы избежать проблем с локальным временем
    dateTime.setTimeSpec(Qt::UTC);
    
    if (!dateTime.isValid()) {
        m_error = "Invalid date format: " + dateTimeStr + ". Expected formats: dd.MM.yyyy HH:mm or dd.MM.yyyy <total minutes from start of day>";
        return false;
    }
    return true;
} 