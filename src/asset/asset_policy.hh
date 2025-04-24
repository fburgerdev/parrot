#pragma once

namespace Parrot {
  /// @brief Determines, when Assets are loaded into memory.
  enum class LoadingPolicy {
    LAZY_LOAD, ///< Load an Asset into memory only if it's used
  };
  /// @brief Determines, when Assets are released from memory.
  enum class UnloadingPolicy {
    UNLOAD_NEVER, ///< Release an Asset only when the AssetManager is destroyed
    UNLOAD_UNUSED, ///< Release an Asset instantly when it's unused
  };
}