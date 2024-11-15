#include "common.hh"
#include "guard.hh"

namespace Parrot {
	// ContextGuard
	ContextGuard::ContextGuard(const function<void()>& bind, const function<void()>& unbind)
		: _unbind(unbind) {
		bind();
	}
	// ~ContextGuard
	ContextGuard::~ContextGuard() {
		_unbind();
	}
}