#pragma once

#include "Types.h"

namespace ECS {

	class BaseSystem {
	public:
		BaseSystem() = default;
		virtual ~BaseSystem() = default;

		void RemoveEntity(const EntityID entity) {
			entities.erase(entity);
		}

		void AddEntity(const EntityID entity) {
			entities.insert(entity);
		}

		const Signature GetSignature() const {
			return signature;
		}

		template<typename T>
		void AddComponentSignature() {
			signature.insert(CompType<T>());
		}

		virtual void Start() { }
		virtual void Update() { 
			for (auto i : entities) { 
				std::cout << i << " ";
			}
			std::cout << std::endl;
		}
		virtual void Render() { }
		virtual void Destroy() { }

	protected:
		friend class EntityManager;
		Signature signature;
		std::set<EntityID> entities;
	};
}