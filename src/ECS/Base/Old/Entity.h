#pragma once

#include "EntityManager.h"

namespace ECS {

	class Entity {

	public:
		Entity(const EntityID id, EntityManager* manager) : ID(id), MGR(manager) { }
		~Entity() = default;

		const EntityID GetID() const {
			return ID;
		}

		template<typename T, typename... Args>
		void AddComponent(Args&&... args) {
			MGR->AddComponent<T>(ID, std::forward<Args>(args)...);
		}

		template<typename T>
		void AddComponent(T& component) {
			MGR->AddComponent<T>(ID, component);
		}

		template<typename T>
		inline T& GetComponent() {
			return MGR->GetComponent<T>(ID);
		}

		template<typename T>
		inline void RemoveComponent() {
			MGR->RemoveComponent<T>(ID);
		}

		template<typename T>
		inline bool HasComponent() {
			return MGR->HasComponent<T>(ID);
		}

		void Destroy() {
			MGR->DestroyEntity(ID);
		}

	private:
		EntityID ID;
		EntityManager* MGR;
	};
}