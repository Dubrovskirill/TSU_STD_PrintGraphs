#include "jsondatasource.h"
#include <QFile>
#include <QDebug>

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

    // Парсим данные
    // QDateTime baseTime; // Больше не нужна для оси времени
    // bool isFirst = true; // Больше не нужна для оси времени

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
    dateTime = QDateTime::fromString(dateTimeStr, "dd.MM.yyyy HH:mm");
    // Устанавливаем временную зону UTC, чтобы избежать проблем с локальным временем
    dateTime.setTimeSpec(Qt::UTC);
    if (!dateTime.isValid()) {
        m_error = "Invalid date format: " + dateTimeStr + ". Expected format: dd.MM.yyyy HH:mm";
        return false;
    }
    return true;
} 