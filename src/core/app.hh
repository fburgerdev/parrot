#pragma once
#include "asset/manager.hh"

namespace Parrot {
	// App
	class App {
	public:
		// App
		App(const stdf::path& asset_dir);
		// run
		void run();
	private:
		AssetManager _asset_manager;
	};
}