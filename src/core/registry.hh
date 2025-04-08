#pragma once
#include "common.hh"

namespace Parrot{
  using TypeID = usize;
  template<class Base, class... Args>
  using RegistryFactory = Func<UniquePtr<Base>(Args&&...)>;
  template<class Base, class... Args>
  using RegistryEntry = Pair<TypeID, RegistryFactory<Base, Args...>>;

  template<class Base, class... Args>
  extern Map<string, RegistryEntry<Base, Args...>> g_registry;
}