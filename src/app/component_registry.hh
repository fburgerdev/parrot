#pragma once
#include "ecs/basic_component.hh"
#include "graphics/camera.hh"
#include "graphics/light.hh"
#include "graphics/render_object.hh"

namespace Parrot {
  using CameraComponent = BasicComponent<Camera>;
  using LightComponent = BasicComponent<Light>;
  using RenderObjectComponent = BasicComponent<RenderObject>;
}