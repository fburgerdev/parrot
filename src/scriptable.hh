#pragma once
#include "common.hh"

namespace Parrot {
	// forward: Event
	class Event;
	// EventResolver
	using EventResolver = function<bool(const Event&)>;

	// Script
	class Script {
	public:
		// Script
		Script() = default;

		// onUpdate
		virtual void onUpdate(float32 delta_time);
		// resolveEvent
		virtual bool resolveEvent(const Event& e);

		// friend: Scriptable
		friend class Scriptable;
	private:
		// onAttach / onDetach
		virtual void onAttach();
		virtual void onDetach();
	};
	// getScriptID
	template<class T>
	usize getScriptID() {
		return typeid(T).hash_code();
	}

	// Scriptable
	class Scriptable {
	public:
		// Scriptable / ~Scriptable
		Scriptable() = default;
		Scriptable(Scriptable* parent);
		Scriptable(const Scriptable&) = delete;
		Scriptable(Scriptable&&) = default;
		~Scriptable();
		// =
		Scriptable& operator=(const Scriptable&) = delete;
		Scriptable& operator=(Scriptable&&) = default;

		// foreachChild
		virtual void foreachChild(function<void(Scriptable&)> func) = 0;
		virtual void foreachChild(function<void(const Scriptable&)> func) const = 0;

		// resolveEvent
		bool resolveEvent(const Event& e);
		// raiseEvent
		void raiseEvent(const Event& e);
		// update
		void update(float32 delta_time);

		// getScript
		template<class T> requires std::is_base_of_v<Script, T>
		T& getScript() {
			auto it = _scripts.find(getScriptID<T>());
			//TODO: assert(it != _scripts.end())
			return reinterpret_cast<T&>(*it->second);
		}
		template<class T> requires std::is_base_of_v<Script, T>
		const T& getScript() const {
			auto it = _scripts.find(getScriptID<T>());
			//TODO: assert(it != _scripts.end())
			return reinterpret_cast<const T&>(*it->second);
		}
		// addScript
		void addScript(usize id, UniquePtr<Script>&& script) {
			_scripts.emplace(id, std::move(script));
		}
		template<class T, class... Args> requires std::is_base_of_v<Script, T>
		T& addScript(Args&&... args) {
			auto result = _scripts.emplace(getScriptID<T>(), std::make_unique<T>(std::forward<Args>(args)...));
			auto& script = result.first->second;
			//TODO: assert(result.second)
			script->onAttach();
			return reinterpret_cast<T&>(*script);
		}
		// removeScript
		template<class T> requires std::is_base_of_v<Script, T>
		void removeScript() {
			auto it = _scripts.find(getScriptID<T>());
			//TODO: assert(it != _scripts.end())
			it->second.onDetach();
			_scripts.erase(it);
		}
	private:
		bool captureEvent(const Event& e);
		bool bubbleEvent(const Event& e);

		Scriptable* _parent = nullptr;
		HashMap<usize, UniquePtr<Script>> _scripts;
	};
	// makeSingleScriptable
	template<class T, class... Args> requires std::is_base_of_v<Script, T>
	Scriptable makeSingleScriptable(Args&&... args) {
		Scriptable out;
		out.addScript<T>(std::forward<Args>(args)...);
		return out;
	}
}