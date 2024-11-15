#pragma once

namespace Parrot {
	// Component
	class Component {
	public:

	};

	// getComponentID
	template<class T>
	usize getComponentID() {
		return typeid(T).hash_code();
	}
}