#pragma once
#include "window/window.hh"
#include "graphics/context.hh"

namespace Parrot {
	// GPU
	class GPU {
	public:
		// context
		GPUContext& context(Window& window);
	private:
		Map<Window*, GPUContext> _contexts;
	};
}