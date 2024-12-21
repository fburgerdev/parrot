#version 330 core
// in
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_tex_coords;
// out
out vec3 v_position;
out vec3 v_normal;
out vec2 v_tex_coords;

// uniform
uniform mat4 u_model;
uniform mat4 u_model_rot;

void main() {
    // position
    gl_Position = u_world_to_clip * u_model * vec4(a_pos, 1);

    // out
    v_tex_coords = a_tex_coords;
    v_position = (u_model * vec4(a_pos, 1)).xyz;
    v_normal = (u_model_rot * vec4(a_normal, 0)).xyz;
}