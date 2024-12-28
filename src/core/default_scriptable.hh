#pragma once
#include "scriptable.hh"

namespace Parrot {
	// forward: App
	class App;
	// DefaultScriptable
	class DefaultScriptable : public Scriptable {
	public:
		// DefaultScriptable / ~DefaultScriptable
		DefaultScriptable(App& app);
		~DefaultScriptable();

		// foreachChild
		virtual void foreachChild(function<void(Scriptable&)> func) override;
		virtual void foreachChild(function<void(const Scriptable&)> func) const override;
	private:
		App& _app;
	};
}