#pragma once

namespace ECS {

	class Entity;
	class BaseSystem;
	class BaseComponent;
	class EntityManager;

	// global constantes
	constexpr int INVALID_TYPE_ID = 0;
	constexpr int INVALID_ENTITY = -1;
	constexpr int MAX_COMP_COUNT = 32;
	constexpr int MAX_ENTITY_COUNT = 5000;

	// typedefs
	using EntityID = int;
	using SystemTypeID = int;
	using ComponentTypeID = int;
	using Signature = std::set<ComponentTypeID>;
	using FactoryType = std::shared_ptr<BaseComponent>;

	// Runtime type
	inline int GetRuntimeTypeID() {
		static int typeID = 1u;
		return typeID++;
	}

	template<typename T>
	inline SystemTypeID SystemType() noexcept {
		static_assert((std::is_base_of<BaseSystem, T>::value && !std::is_same<BaseSystem, T>::value), "Invalid template type");
		static const SystemTypeID typeID = GetRuntimeTypeID();
		return typeID;
	}

	template<typename T>
	inline ComponentTypeID CompType() noexcept {
		static_assert((std::is_base_of<BaseComponent, T>::value && !std::is_same<BaseComponent, T>::value), "Invalid template type");
		static const ComponentTypeID typeID = GetRuntimeTypeID();
		return typeID;
	}
}


