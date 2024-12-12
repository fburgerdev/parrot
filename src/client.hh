#pragma once
// global
#include "registry.hh"
#include "scriptable.hh"
// core
#include "core/app.hh"
#include "core/playing_unit.hh"
// ecs
#include "ecs/component.hh"
#include "ecs/entity.hh"
#include "ecs/scene.hh"
// window
#include "window/window.hh"
#include "window/event.hh"
// math
#include "math/basic.hh"
#include "math/matrix.hh"
#include "math/3d.hh"

namespace Parrot {
	// EntityScript
	class EntityScript : public Script {
	public:
		// EntityScript
		EntityScript(Entity& entity)
			: entity(&entity) {}

		// Entity
		Entity* entity;
	private:
		// setScriptOwner
		virtual void setScriptOwner(Scriptable* owner) {
			entity = (Entity*)owner; //TODO: use c++ style cast
		}
	};
	// SceneScript
	class SceneScript : public Script {
	public:
		// SceneScript
		SceneScript(Scene& scene)
			: scene(&scene) {}

		// Scene
		Scene* scene;
	private:
		// setScriptOwner
		virtual void setScriptOwner(Scriptable* owner) {
			scene = (Scene*)owner; //TODO: use c++ style cast
		}
	};
	// WindowScript
	class WindowScript : public Script {
	public:
		// WindowScript
		WindowScript(Window& window)
			: window(&window) {}

		// Window
		Window* window;
	private:
		// setScriptOwner
		virtual void setScriptOwner(Scriptable* owner) {
			window = (Window*)(owner); //TODO: use c++ style cast
		}
	};
	// AppScript
	class AppScript : public Script {
	public:
		// AppScript
		AppScript(App& app)
			: app(&app) {}

		// App
		App* app;
	private:
		// setScriptOwner
		virtual void setScriptOwner(Scriptable* owner) {
			app = (App*)(owner); //TODO: use c++ style cast
		}
	};
}