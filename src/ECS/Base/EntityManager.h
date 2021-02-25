#pragma once

#include "Types.h"
#include "CompList.h"
#include "BaseSystem.h"
#include "BaseComponent.h"

namespace ECS {

	class EntityManager {

	public:
		EntityManager(): entityCount(0) {
			for (EntityID entity = 0u; entity < MAX_ENTITY_COUNT; entity++) {
				availableEntities.push(entity);
			}
		}

		~EntityManager() {

		}

		void Update() {
			for (auto& system : registeredSystems) {
				system.second->Update();
			}
		}

		void Render() {
			for (auto& system : registeredSystems) {
				system.second->Render();
			}
		}

		const EntityID AddNewEntity() {
			const EntityID entity = availableEntities.front();
			AddEntitySignature(entity);
			availableEntities.pop();
			entityCount++;
			return entity;
		}

		void DestroyEntity(const EntityID entity) {
			assert(entity < MAX_ENTITY_COUNT && "EntityID our of range!");

			entitiesSignatures.erase(entity);
			for (auto& array : componentsArrays) {
				array.second->Erase(entity);
			}

			for (auto& system : registeredSystems) {
				system.second->RemoveEntity(entity);
			}

			entityCount--;
			availableEntities.push(entity);
		}

		template<typename T, typename... Args>
		void AddComponent(const EntityID entity, Args&&... args) {
			assert(entity < MAX_ENTITY_COUNT && "EntityID out of range");
			assert(GetEntitySignature(entity)->size() < MAX_COMP_COUNT && "Component count limit reached!");

			T component(std::forward<Args>(args)...);
			component.entityID = entity;		
			GetEntitySignature(entity)->insert(CompType<T>());
			GetCompList<T>()->Insert(component);
			UpdateEntityTargetSystems(entity);
		}

		template<typename T, typename... Args>
		void AddComponent(const EntityID entity, T& component) {
			assert(entity < MAX_ENTITY_COUNT && "EntityID out of range");
			assert(GetEntitySignature(entity)->size() < MAX_COMP_COUNT && "Component count limit reached!");
			component.entityID = entity;
			GetEntitySignature(entity)->insert(CompType<T>());
			GetCompList<T>()->Insert(component);
			UpdateEntityTargetSystems(entity);
		}

		template<typename T>
		void RemoveComponent(const EntityID entity) {
			assert(entity < MAX_ENTITY_COUNT && "EntityID out of range");
			const ComponentTypeID compType = CompType<T>();
			GetEntitySignature(entity)->erase(compType);
			GetCompList<T>()->Erase(entity);
			UpdateEntityTargetSystems(entity);
		}

		template<typename T>
		T& GetComponent(const EntityID entity) {
			assert(entity < MAX_ENTITY_COUNT && "EntityID out of range");
			return GetCompList<T>()->Get(entity);
		}

		template<typename T>
		const bool HasComponent(const EntityID entity) {
			assert(entity < MAX_ENTITY_COUNT && "EntityID out of range");
			return (GetEntitySignature(entity)->count(CompType<T>()) > 0);
		}

		//---------------------------------------------------------------------

		template<typename T>
		void RegisterSystem(){
			const SystemTypeID systemType = SystemType<T>();
			assert(registeredSystems.count(systemType) == 0 && "System already registered!");
			auto system = std::make_shared<T>();

			// add entity to new system
			for (EntityID entity = 0; entity < entityCount; entity++) {
				AddEntityToSystem(entity, system.get());
			}

			system->Start();
			registeredSystems[systemType] = std::move(system);
		}

		template<typename T>
		void UnRegisterSystem() {
			const SystemTypeID systemType = SystemType<T>();
			assert(registeredSystems.count(systemType) != 0 && "System not registered!");
			registeredSystems.erase(systemType);
		}

	private:

		template<typename T>
		void AddCompList() {
			const ComponentTypeID compType = CompType<T>();
			assert(componentsArrays.find(compType) == componentsArrays.end() && "Component list already registered!");
			componentsArrays[compType] = std::move(std::make_shared<CompList<T>>());
		}

		template<typename T>
		std::shared_ptr<CompList<T>> GetCompList() {
			const ComponentTypeID compType = CompType<T>();
			if (componentsArrays.count(compType) == 0) { AddCompList<T>(); }
			return std::static_pointer_cast<CompList<T>>(componentsArrays.at(compType));
		}

		void AddEntitySignature(const EntityID entity) {
			assert(entitiesSignatures.find(entity) == entitiesSignatures.end() && "Signature not found");
			entitiesSignatures[entity] = std::move(std::make_shared<Signature>());
		}

		std::shared_ptr<Signature> GetEntitySignature(const EntityID entity) {
			assert(entitiesSignatures.find(entity) != entitiesSignatures.end() && "Signature not found");
			return entitiesSignatures.at(entity);
		}

		void UpdateEntityTargetSystems(const EntityID entity) {
			for (auto& system : registeredSystems) {
				AddEntityToSystem(entity, system.second.get());
			}
		}

		void AddEntityToSystem(const EntityID entity, BaseSystem* system) {
			if (BelongToSystem(entity, system->signature)) {
				system->entities.insert(entity);
			}
			else {
				system->entities.erase(entity);
			}
		}

		bool BelongToSystem(const EntityID entity, const Signature& system_signature) {
			for (const auto compType : system_signature) {
				if (GetEntitySignature(entity)->count(compType) == 0) {
					return false;
				}
			}
			return true;
		}

	private:
		EntityID entityCount;
		std::queue<EntityID> availableEntities;
		std::map<EntityID, std::shared_ptr<Signature>> entitiesSignatures;
		std::map<SystemTypeID, std::shared_ptr<BaseSystem>> registeredSystems;
		std::map<ComponentTypeID, std::shared_ptr<ICompList>> componentsArrays;
	};
}
