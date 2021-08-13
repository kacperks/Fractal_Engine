#pragma once

#include "Types.h"

namespace ECS {

	class BaseSystem {
	public:
		BaseSystem() = default;
		virtual ~BaseSystem() = default;

		inline const Signature GetSignature() const { return signature; }

		inline void EraseEntity(const EntityID entity) { entities.erase(entity); }
		inline void PushEntity(const EntityID entity) { entities.insert(entity); }

		template<typename T>
		inline void AddComponentSignature() { signature.insert(CompType<T>()); }	

		inline const bool IsEmpty() const { return (entities.size() == 0);}
		inline const bool HasEntity(EntityID entity) const { return (entities.count(entity) > 0);}

		virtual void Stop() {}
		virtual void Start() {}
		virtual void Render() {}
		virtual void Update() {}
		virtual void Awake() {}

	protected:
		Signature signature;
		std::set<EntityID> entities;
	};
}
