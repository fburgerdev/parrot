#pragma once
#include "playing_unit.hh"
#include "asset/manager.hh"

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

	// App
	class App : public Scriptable {
	public:
		// App / ~App
		App(const stdf::path& config_path);
		App(App&&) = default;
		~App();
		// =
		App& operator=(App&&) = default;

		// add
		PlayingUnit& add(const WindowConfig& window_config, const SceneConfig& scene_config);
		// getPlayingUnit
		PlayingUnit& getPlayingUnit(const Window& window);
		const PlayingUnit& getPlayingUnit(const Window& window) const;
		PlayingUnit& getPlayingUnit(const Scene& scene);
		const PlayingUnit& getPlayingUnit(const Scene& scene) const;

		// run
		void run();

		// foreachChild
		virtual void foreachChild(function<void(Scriptable&)> func) override;
		virtual void foreachChild(function<void(const Scriptable&)> func) const override;
	private:
		string _name;
		PlayingUnit* _main_unit = nullptr;
		Map<uuid, PlayingUnit> _units;
		AssetManager _asset_manager;
		DefaultScriptable _default_scriptable;
	};
}