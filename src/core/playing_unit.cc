#include "common.hh"
#include "playing_unit.hh"

namespace Parrot {
	// PlayingUnit
	PlayingUnit::PlayingUnit(Window&& window, Scene&& scene, HandleResolver resolver, Scriptable* parent)
	  : Scriptable(parent), window(std::move(window)), scene(std::move(scene)), _gpu_context(resolver) {}
	
	// foreachChild
	void PlayingUnit::foreachChild(function<void(Scriptable&)> func) {
		func(scene.getRoot());
	}
	void PlayingUnit::foreachChild(function<void(const Scriptable&)> func) const {
		func(scene.getRoot());
	}
}