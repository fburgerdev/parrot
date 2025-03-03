#pragma once
#include "camera.hh"
#include "light_source.hh"
#include "render_object.hh"
#include "utils/math_3d.hh"

namespace Parrot {
  // RenderData
  struct RenderData {
    Pair<const Transform<>*, const Camera*> camera = { nullptr, nullptr };
    Set<Pair<const Transform<>*, const LightSource*>> lights;
    Set<Pair<const Transform<>*, const RenderObject*>> opaque_objects;
    List<Pair<const Transform<>*, const RenderObject*>> translucent_objects;
  };
}