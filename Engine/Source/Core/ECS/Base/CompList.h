#pragma once

#include "Types.h"

namespace ECS {		

	class ICompList {
	public:
		ICompList() = default;
		virtual ~ICompList() = default;
		virtual void Erase(const EntityID entity) { }
		virtual void Insert(BaseComponent* component) { }
		const ComponentTypeID GetDataType() const { return typeID; }
	protected:
		ComponentTypeID typeID = INVALID_TYPE_ID;
	};

	template<typename T>
	class CompList : public ICompList {

	public:
		~CompList() = default;		
		CompList(): data({}) {
			typeID = CompType<T>();
		}

		void Insert(BaseComponent* component) override {
			T comp = *(static_cast<T*>(component));
			auto it = std::find_if(data.begin(), data.end(), [&comp](const T& c) { return c.GetID() == comp.GetID(); });
			assert(it == data.end() && "Trying to insert duplicate of component!");		
			data.push_back(comp);
		}

		T& Get(const EntityID entity) {
			auto it = std::find_if(data.begin(), data.end(), [&](const T& comp) { return comp.GetID() == entity; });
			assert(it != data.end() && "Trying to get non-existing component!");				
			return *it;
		}

		void Erase(const EntityID entity) override {
			auto it = std::find_if(data.begin(), data.end(), [&entity](const T& comp) { return comp.GetID() == entity; });
			if (it != data.end()) {
				data.erase(it);
			}
		}		

	private:	
		std::vector<T> data;		
	};
}
