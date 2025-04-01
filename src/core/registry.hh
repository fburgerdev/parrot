#pragma once
#include "common.hh"

namespace Parrot{
  // TypeID
  using TypeID = usize;
  // RegistryFactory
  template<class Base, class... Args>
  using RegistryFactory = Func<UniquePtr<Base>(Args&&...)>;
  // RegistryEntry
  template<class Base, class... Args>
  using RegistryEntry = Pair<TypeID, RegistryFactory<Base, Args...>>;

  // (global) registry
  template<class Base, class... Args>
  extern Map<string, RegistryEntry<Base, Args...>> g_registry;
}