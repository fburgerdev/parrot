#pragma once
#include "common.hh"

namespace Parrot {
  using seconds = float32;

  class Stopwatch {
  public:
    Stopwatch();

    seconds elapsed() const;
    seconds reset();
  private:
    uint64 _begin = 0;
  };

  inline const Stopwatch g_global_watch;
}