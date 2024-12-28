#pragma once
#include "core/scriptable.hh"
#include "entity_config.hh"

namespace Parrot {
	// Entity
	class Entity : public UUIDObject, public Scriptable {
	public:
		// Entity / ~Entity
		Entity(Scriptable* parent = nullptr);
		Entity(Entity* parent);
		Entity(const EntityConfig& config, AssetHandleResolver resolver, Scriptable* parent = nullptr);
		Entity(const EntityConfig& config, AssetHandleResolver resolver, Entity* parent);
		Entity(Entity&&) = default;
		~Entity();
		// =
		Entity& operator=(Entity&&) = default;

		// parent
		// :: has
		bool hasParent() const;
		// :: get
		Entity& getParent();
		const Entity& getParent() const;

		// child
		// :: create
		Entity& createChild();
		// :: destroy
		void destroyChild(uuid id);
		void destroyChild(const Entity& child);
		// :: foreach
		void foreachChild(function<void(Entity&)> func);
		void foreachChild(function<void(const Entity&)> func) const;
		// :: foreach (scriptable)
		virtual void foreachChild(function<void(Scriptable&)> func) override;
		virtual void foreachChild(function<void(const Scriptable&)> func) const override;

		// component
		// :: has
		template<class T>
		bool hasComponent() const {
			return _components.contains(getComponentID<T>());
		}
		// :: get
		template<class T>
		T& getComponent() {
			return dynamic_cast<T&>(*_components.at(getComponentID<T>()));
		}
		template<class T>
		const T& getComponent() const {
			return dynamic_cast<const T&>(*_components.at(getComponentID<T>()));
		}
		// :: add
		template<class T, class... TArgs>
		T& addComponent(TArgs&&... args) {
			_components.emplace(getComponentID<T>(), std::make_unique<T>(*this, std::forward<TArgs>(args)...));
			return getComponent<T>();
		}
		// :: remove
		template<class T>
		void removeComponent() {
			_components.erase(getComponentID<T>());
		}

		// update
		void update(float32 delta_time);

		// transform
		Transform<> transform;
	private:
		Entity(uuid id, Entity* parent);

		string _tag;
		Entity* _parent = nullptr;
		Map<uuid, Entity> _children;
		Map<usize, UniquePtr<Component>> _components; //? think about reducing indirection
	};
}