#include "common.hh"
#include "surface_opengl.hh"

namespace Parrot {
    namespace OpenGL {
        // (global) surface_snippet
        const ShaderSource g_surface_snippet = string(R""""(
[[snippet "surface"]]
// light
const uint MAX_LIGHT_COUNT = uint(50); 
// :: ambient
struct AmbientLight {
    float intensity;
    vec3 color;
};
// :: directional
struct DirectionalLight {
    vec3 direction;
    float intensity;
    vec3 color;
};

// std
layout (std140) uniform u_std {
    // world_to_clip
    mat4 u_world_to_clip;

    // light
    // :: ambient
    uint u_ambient_count;
    AmbientLight u_ambient_lights[MAX_LIGHT_COUNT];
    // :: directional
    uint u_directional_count;
    DirectionalLight u_directional_lights[MAX_LIGHT_COUNT];
};

// applyLighting
vec3 applyLighting(vec3 in_color, vec3 position, vec3 normal) {
    vec3 out_color = vec3(0);
    // ambient
    for (uint i = uint(0); i < u_ambient_count; ++i) {
        out_color += u_ambient_lights[i].intensity * u_ambient_lights[i].color * in_color;
    }
    // directional
    for (uint i = uint(0); i < u_directional_count; ++i) {
        float factor = clamp(dot(u_directional_lights[i].direction, -normal), 0, 1);
        out_color += factor * u_directional_lights[i].intensity * u_directional_lights[i].color * in_color;
    }
    return out_color;
}
[[end]]
)"""");
    }
}