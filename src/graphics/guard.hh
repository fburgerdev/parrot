#pragma once
#include "common.hh"

namespace Parrot {
	// ContextGuard
	class ContextGuard {
	public:
		// ContextGuard
		ContextGuard(const function<void()>& bind, const function<void()>& unbind);
		ContextGuard(const ContextGuard&) = delete;
		ContextGuard(ContextGuard&&) = delete;
		// ~ContextGuard
		~ContextGuard();
	private:
		function<void()> _unbind;
	};
}