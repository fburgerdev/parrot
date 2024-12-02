#include "common.hh"
#include "playing_unit.hh"

namespace Parrot {
	// PlayingUnit
	PlayingUnit::PlayingUnit(Window&& window, Scene&& scene, Scriptable* parent)
	  : Scriptable(), window(std::move(window)), scene(std::move(scene)) {
		_gpu_context = GPUContext([&] { this->window.bind(); }, [&] { this->window.unbind(); });
	}
}