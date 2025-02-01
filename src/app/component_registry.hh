#pragma once
#include "ecs/component.hh"
#include "graphics/camera.hh"
#include "graphics/light_source.hh"
#include "graphics/render_object.hh"

namespace Parrot {
  // Component
  using CameraComponent = DerivedComponent<Camera>;
  using LightSourceComponent = DerivedComponent<LightSource>;
  using RenderObjectComponent = DerivedComponent<RenderObject>;
}