#pragma once
#include "scriptable.hh"
#include "entity_config.hh"
#include "component.hh"

namespace Parrot {
	// Entity
	class Entity : public UUIDObject, public Scriptable {
	public:
		// Entity / ~Entity
		Entity(Scriptable* parent = nullptr);
		Entity(Entity* parent);
		Entity(const EntityConfig& config, HandleResolver resolver, Scriptable* parent = nullptr);
		Entity(const EntityConfig& config, HandleResolver resolver, Entity* parent);
		Entity(Entity&&) = default;
		~Entity();
		// =
		Entity& operator=(Entity&&) = default;

		// hasParent
		bool hasParent() const;
		// getParent
		Entity& getParent();
		const Entity& getParent() const;

		// createChild
		//Entity& createChild();
		//Entity& createChild(stdf::path& filepath);
		// destroyChild
		void destroyChild(uuid uuid);
		void destroyChild(const Entity& child);
		// foreachChild
		void foreachChild(function<void(Entity&)> func);
		void foreachChild(function<void(const Entity&)> func) const;
		virtual void foreachChild(function<void(Scriptable&)> func) override;
		virtual void foreachChild(function<void(const Scriptable&)> func) const override;

		// hasComponent
		template<class T>
		bool hasComponent() const {
			return _components.contains(getComponentID<T>());
		}
		// getComponent
		template<class T>
		T& getComponent() {
			return dynamic_cast<T&>(*_components.at(getComponentID<T>()));
		}
		template<class T>
		const T& getComponent() const {
			return dynamic_cast<const T&>(*_components.at(getComponentID<T>()));
		}
		// addComponent
		template<class T, class... TArgs>
		T& addComponent(TArgs&&... args) {
			_components.emplace(getComponentID<T>(), std::make_unique<T>(*this, std::forward<TArgs>(args)...));
			return getComponent<T>();
		}
		// removeComponent
		template<class T>
		void removeComponent() {
			_components.erase(getComponentID<T>());
		}

		// friend
		friend class Scene;

		// transform
		Transform<> transform;
	private:
		Entity(uuid uuid, Entity* parent);
		void update(float32 delta_time);

		string _tag;
		Entity* _parent = nullptr;
		Map<uuid, UniquePtr<Entity>> _children; //? think about reducing indirection
		Map<usize, UniquePtr<Component>> _components; //? think about reducing indirection
	};
}