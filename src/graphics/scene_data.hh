#pragma once
#include "camera.hh"
#include "light_source.hh"
#include "render_object.hh"
#include "utils/math_3d.hh"

namespace Parrot {
  // SceneData
  struct SceneData {
    Pair<const Transform<>*, const Camera*> camera = { nullptr, nullptr };
    Set<Pair<const Transform<>*, const LightSource*>> lights;
    Set<Pair<const Transform<>*, const RenderObject*>> render_objects;
  };
}