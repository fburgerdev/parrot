#include "common.hh"
#include "gpu.hh"

namespace Parrot {
	// context
	GPUContext& GPU::context(Window& window) {
		if (!_contexts.contains(&window)) {
			_contexts.emplace(&window, GPUContext([&] { window.bind(); }, [&] { window.unbind(); }));
		}
		return _contexts.at(&window);
	}
}