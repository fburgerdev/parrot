[[vertex(330 core)]]
// in
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_tex_coords;
// out
out vec3 v_position;
out vec3 v_normal;
out vec2 v_tex_coords;

// camera + lighting
[[include "surface"]]

// model
uniform mat4 u_local_to_world;
uniform mat4 u_local_to_world_normal;

// (snippet) global
[[include "vertex-global" optional]]

// main
void main() {
    // (snippet) prefix
    [[include "vertex-prefix" optional]]
    
    // position
    gl_Position = u_world_to_clip * u_local_to_world * vec4(a_pos, 1);

    // out
    v_position = (u_local_to_world * vec4(a_pos, 1)).xyz;
    v_normal = (u_local_to_world_normal * vec4(a_normal, 0)).xyz;
    v_tex_coords = a_tex_coords;
    
    // (snippet) postfix
    [[include "vertex-postfix" optional]]
}
[[end]]

[[fragment(330 core)]]
// in
in vec3 v_position;
in vec3 v_normal;
in vec2 v_tex_coords;
// out
out vec4 o_frag_color; 

// camera + lighting
[[include "surface"]]

// texture + tint
uniform sampler2D u_texture;
uniform vec3 u_tint = vec3(1, 1, 1);
vec3 sample(vec2 tex_coords) {
    return texture(u_texture, tex_coords).rgb * u_tint;
}

// (snippet) global
[[include "fragment-global" optional]]

// main
void main() {
    // (snippet) prefix
    [[include "fragment-prefix" optional]]

    // out
    vec3 color = applyLighting(sample(v_tex_coords), v_position, v_normal);
    o_frag_color = vec4(color, 1);
    
    // (snippet) postfix
    [[include "fragment-postfix" optional]]
}
[[end]]