#pragma once

namespace Parrot {
  enum class LoadingPolicy {
    /* PRELOAD_APP, PRELOAD_SCENE, */ LAZY_LOAD
  };
  enum class UnloadingPolicy {
    UNLOAD_APP, /* UNLOAD_SCENE, */ UNLOAD_UNUSED
  };
}