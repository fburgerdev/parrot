#include "common.hh"
#include "app.hh"
#include "window/window.hh"
#include "debug/debug.hh"

namespace Parrot {
	// App
	App::App(const stdf::path& asset_dir)
		: _asset_manager(asset_dir) {}
	// run
	void App::run() {

	}
}