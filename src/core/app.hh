#pragma once
#include "playing_unit.hh"
#include "asset/manager.hh"
#include "graphics/batch_renderer.hh"

namespace Parrot {
	// App
	class App : public Scriptable {
	public:
		// App
		App(const stdf::path& config_path);

		// add
		PlayingUnit& add(const WindowConfig& window_config, const SceneConfig& scene_config);
		// run
		void run();
	private:
		void draw(PlayingUnit& unit);

		string _name;
		PlayingUnit* _main_unit = nullptr;
		Map<uuid, PlayingUnit> _units;
		AssetManager _asset_manager;
		Scriptable _default_scriptable;
	};
}