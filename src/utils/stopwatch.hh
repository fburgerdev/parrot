#pragma once
#include "common.hh"

namespace Parrot {
  using seconds = float32;

  /// @ingroup Utils
  /// @brief Measure time differences.
  class Stopwatch {
  public:
    /// @brief Construct Stopwatch starting from 0.
    Stopwatch();

    /// @brief Get elapsed time.
    /// @return Seconds elapsed since the last reset (or construction) 
    seconds elapsed() const;
    /// @brief Reset Stopwatch.
    /// @return Seconds elapsed since the last reset (or construction) 
    seconds reset();
  private:
    uint64 _begin = 0;
  };

  inline const Stopwatch g_global_watch;
}