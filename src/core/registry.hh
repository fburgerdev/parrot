#pragma once
#include "common.hh"

namespace Parrot{
	// TypeID
	using TypeID = usize;
	// Factory
	template<class Base, class... Args>
	using Factory = function<UniquePtr<Base>(Args&&...)>;
	// RegistryEntry
	template<class Base, class... Args>
	using RegistryEntry = Pair<TypeID, Factory<Base, Args...>>;

	// (global) registry
	template<class Base, class... Args>
	extern Map<string, RegistryEntry<Base, Args...>> g_registry;
}