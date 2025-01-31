#pragma once

namespace Parrot {
  // LoadingPolicy
  enum class LoadingPolicy {
    /* PRELOAD_APP, PRELOAD_SCENE, */ LAZY_LOAD
  };
  // UnloadingPolicy
  enum class UnloadingPolicy {
    UNLOAD_APP, /* UNLOAD_SCENE, */ UNLOAD_UNUSED
  };
}