#version 330 core
// out
out vec4 o_frag_color; 
// in
in vec2 v_tex_coords;
in float v_intensity;

// constants
const vec3 background_color = vec3(0.7, 0.7, 0.9);

// uniform
uniform sampler2D u_texture;
uniform vec3 u_tint = vec3(1, 1, 1);

void main() {
    o_frag_color = texture(u_texture, v_tex_coords) * v_intensity + vec4(background_color, 1) * (1 - v_intensity);
}