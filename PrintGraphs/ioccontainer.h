#ifndef IOCCONTAINER_H
#define IOCCONTAINER_H

#include <QSharedPointer>
#include <QMap>
#include <QVariant>
#include <functional>

// Простой IoC-контейнер
class IoCContainer
{
public:
    // Регистрация типа с функцией создания
    template<typename T>
    void registerType(std::function<QSharedPointer<T>()> creator)
    {
        creators_[typeid(T).name()] = [creator]() -> QVariant {
            return QVariant::fromValue(creator());
        };
    }

    // Получение экземпляра
    template<typename T>
    QSharedPointer<T> resolve()
    {
        auto it = creators_.find(typeid(T).name());
        if (it != creators_.end()) {
            return it.value()().value<QSharedPointer<T>>();
        }
        return nullptr;
    }

private:
    QMap<QString, std::function<QVariant()>> creators_;
};

#endif // IOCCONTAINER_H
