#pragma once

#include "BaseComponent.h"

namespace ECS {

    using Constructor = std::function<FactoryType()>;

    class ComponentFactory {

    public:
        ~ComponentFactory() = default;
        ComponentFactory(const ComponentFactory&) = delete;
        ComponentFactory& operator=(const ComponentFactory&) = delete;
        static ComponentFactory& Ref() {
            static ComponentFactory reference;
            return reference;
        }

        auto CreateComponent(const char* typeName) {            
            auto it = registryFuncs.find(typeName);
            assert(it != registryFuncs.end() && "Component Type not found in registry");
            auto component = it->second();
            return component;
        }

        void RegisterType(ComponentTypeID compType, const char* typeName, Constructor callback) {
            registryFuncs[typeName] = callback;
            registryTypes[typeName] = compType;
        }

        const ComponentTypeID GetTypeID(const char* typeName) {
            assert(registryTypes.find(typeName) != registryTypes.end() && "Typename out of range");
            return registryTypes.at(typeName);
        }

    private:
        ComponentFactory() = default;

    private:
        std::map<const char*, Constructor> registryFuncs;
        std::map<const char*, ComponentTypeID> registryTypes;
    };

    static ComponentFactory& CompFactory = ComponentFactory::Ref();

    template<typename T>
    class Registrar {
    public:
        Registrar(const char* typeName) {
            const ComponentTypeID compType = CompType<T>();
            CompFactory.RegisterType(compType, typeName, []()->FactoryType{ return std::move(std::make_shared<T>()); });
        }
    };

}