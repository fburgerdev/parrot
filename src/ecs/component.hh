#pragma once
#include "common.hh"

namespace Parrot {
  /// @ingroup PublicAPI
  /// @brief Reusable functionality to attach to Entities.
  class Component {
  public:
    /// @note Explicit default constructor because of default destructor
    Component() = default;
    /// @note Virtual destructor for derived Components
    virtual ~Component() = default;

    /// @brief Component specific behaviour every time the game updates.
    /// @param delta_time Seconds elapsed since last update
    virtual void update(float32 delta_time);
    /// @brief Uniquely identify Components using the derived Component type.
    /// @return Unique ID
    virtual usize getID() const = 0;
  };
}