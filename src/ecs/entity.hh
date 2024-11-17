#pragma once
#include "uuid.hh"
#include "component.hh"

namespace Parrot {
	// Entity
	class Entity : public UUIDObject {
	public:
		// getUUID
		uuid getUUID() const;

		// hasParent
		bool hasParent() const;
		// getParent
		Entity& getParent();
		const Entity& getParent() const;

		// createChild
		Entity& createChild();
		Entity& createChild(stdf::path& filepath);
		// destroyChild
		void destroyChild(uuid uuid);
		void destroyChild(const Entity& child);
		// children
		// TODO: iterate children
		
		// hasComponent
		template<class T>
		bool hasComponent() const {
			return _components.contains(getComponentID<T>());
		}
		// getComponent
		template<class T>
		T& getComponent() {
			return dynamic_cast<T*>(_components.at(getComponentID<T>()));
		}
		template<class T>
		const T& getComponent() const {
			return dynamic_cast<T*>(_components.at(getComponentID<T>()));
		}
		// addComponent
		template<class T>
		T& addComponent() {
			_components.emplace(getComponentID<T>());
			return getComponent<T>();
		}
		// removeComponent
		template<class T>
		void removeComponent() {
			_components.erase(getComponentID<T>());
		}
	private:
		Entity(uuid uuid, Entity* parent);

		uuid _uuid;
		Entity* _parent = nullptr;
		Map<uuid, Entity> _children;
		Map<usize, Component> _components;
	};
}