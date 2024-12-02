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
		Scriptable(EventResolver capture, EventResolver bubble);
		Scriptable(const Scriptable&) = delete;
		Scriptable(Scriptable&&) = default;
		~Scriptable();
		// =
		Scriptable& operator=(const Scriptable&) = delete;
		Scriptable& operator=(Scriptable&&) = default;

		// getCaptureCallback / getBubbleCallback
		const EventResolver& getCaptureCallback();
		const EventResolver& getBubbleCallback();
		// raiseEvent
		void raiseEvent(const Event& e);

		// getScript
		template<class U> requires std::is_base_of_v<Script, U>
		U& getScript() {
			auto it = _scripts.find(getScriptID<U>());
			//TODO: assert(it != _scripts.end())
			return reinterpret_cast<U&>(*it->second);
		}
		template<class U> requires std::is_base_of_v<Script, U>
		const U& getScript() const {
			auto it = _scripts.find(getScriptID<U>());
			//TODO: assert(it != _scripts.end())
			return reinterpret_cast<const U&>(*it->second);
		}
		// addScript
		template<class U, class... Args> requires std::is_base_of_v<Script, U>
		U& addScript(Args&&... args) {
			auto result = _scripts.emplace(getScriptID<U>(), std::make_unique<U>(std::forward<Args>(args)...));
			auto& script = result.first->second;
			//TODO: assert(result.second)
			script->onAttach();
			return reinterpret_cast<U&>(*script);
		}
		// removeScript
		template<class U> requires std::is_base_of_v<Script, U>
		void removeScript() {
			auto it = _scripts.find(getScriptID<U>());
			//TODO: assert(it != _scripts.end())
			it->second.onDetach();
			_scripts.erase(it);
		}
	private:
		bool resolveEvent(const Event& e);

		EventResolver _capture, _bubble;
		HashMap<usize, UniquePtr<Script>> _scripts;
	};
}