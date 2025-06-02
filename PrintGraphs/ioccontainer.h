#ifndef IOCCONTAINER_H
#define IOCCONTAINER_H

#include <map>
#include <memory>
#include <functional>
#include <string>
#include <typeindex>

class IOCContainer
{
    static int s_nextTypeId;
    template<typename T>
    static int GetTypeID() {
        static int typeId = s_nextTypeId++;
        return typeId;
    }

public:
    class FactoryRoot
    {
    public:
        virtual ~FactoryRoot() = default;
    };

    std::map<std::pair<std::type_index, std::string>, std::shared_ptr<FactoryRoot>> m_factories;

    template<typename T>
    class CFactory : public FactoryRoot
    {
        std::function<std::shared_ptr<T>()> m_factory;

    public:
        ~CFactory() {}

        CFactory(std::function<std::shared_ptr<T>()> factory)
            : m_factory(factory)
        {}

        std::shared_ptr<T> GetObject() {
            return m_factory();
        }
    };

    template<typename T>
    std::shared_ptr<T> GetObject(const std::string& key = "") {
        auto typeKey = std::make_pair(std::type_index(typeid(T)), key);
        auto it = m_factories.find(typeKey);
        if (it == m_factories.end()) return nullptr;
        
        auto factoryBase = it->second;
        if (!factoryBase) return nullptr;
        
        auto factory = std::static_pointer_cast<CFactory<T>>(factoryBase);
        return factory->GetObject();
    }

    template<typename TInterface, typename... TS>
    void RegisterFunctor(
        std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS>... ts)> functor) {
        m_factories[GetTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>(
                [ = ] { return functor(GetObject<TS>()...); });
    }

    template<typename TInterface>
    void RegisterInstance(std::shared_ptr<TInterface> t) {
        m_factories[GetTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>(
                [ = ] { return t; });
    }

    template<typename TInterface, typename... TS>
    void RegisterFunctor(std::shared_ptr<TInterface> (*functor)(std::shared_ptr<TS>... ts)) {
        RegisterFunctor(
            std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS>... ts)>(functor));
    }

    template<typename TInterface, typename TConcrete, typename... TArguments>
    void RegisterFactory(const std::string& key = "") {
        auto typeKey = std::make_pair(std::type_index(typeid(TInterface)), key);
        m_factories[typeKey] = std::make_shared<CFactory<TInterface>>(
            [] { return std::make_shared<TConcrete>(); });
    }

    template<typename TInterface, typename TConcrete, typename... TArguments>
    void RegisterInstance() {
        RegisterInstance<TInterface>(std::make_shared<TConcrete>(GetObject<TArguments>()...));
    }
};

// Глобальный экземпляр контейнера
extern IOCContainer gContainer;

// Инициализация статической переменной
inline int IOCContainer::s_nextTypeId = 115094801;

#endif // IOCCONTAINER_H 