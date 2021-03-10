#pragma once

#include "Types.h"

namespace ECS {
	struct BaseComponent {
		BaseComponent() = default;
		~BaseComponent() = default;

		inline const EntityID GetID() const { return entityID; }

	private:
		EntityID entityID = -1;
		friend class EntityManager;
	};
}
