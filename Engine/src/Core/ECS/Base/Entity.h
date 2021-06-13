#pragma once

#include "EntityManager.h"

namespace ECS {

	class Entity {
	public:
		Entity() {
			ID = Manager.AddNewEntity();
		}

		const EntityID GetID() const {
			return ID;
		}

		template<typename T, typename... Args>
		void AddComponent(Args&&... args) {
			Manager.AddComponent<T>(ID, std::forward<Args>(args)...);
		}

		template<typename T>
		void AddComponent(T& component) {
			Manager.AddComponent<T>(ID, component);
		}

		template<typename T>
		inline T& GetComponent() {
			return Manager.GetComponent<T>(ID);
		}

		template<typename T>
		inline void RemoveComponent() {
			Manager.RemoveComponent<T>(ID);
		}

		template<typename T>
		inline bool HasComponent() {
			return Manager.HasComponent<T>(ID);
		}

		void Destroy() {
			Manager.DestroyEntity(ID);
		}

	private:
		EntityID ID;
	};
}