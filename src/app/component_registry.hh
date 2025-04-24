#pragma once
#include "ecs/basic_component.hh"
#include "graphics/camera.hh"
#include "graphics/light.hh"
#include "graphics/render_object.hh"

namespace Parrot {
  /// @trivial
  using CameraComponent = BasicComponent<Camera>;
  /// @trivial
  using LightComponent = BasicComponent<Light>;
  /// @trivial
  using RenderObjectComponent = BasicComponent<RenderObject>;
}