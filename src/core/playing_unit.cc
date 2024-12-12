#include "common.hh"
#include "playing_unit.hh"

namespace Parrot {
	// PlayingUnit
	PlayingUnit::PlayingUnit(const WindowConfig& window_config, const SceneConfig& scene_config, HandleResolver resolver, Scriptable* parent)
	  : window(window_config, parent), scene(scene_config, resolver, parent), _gpu_context(resolver) {}
}