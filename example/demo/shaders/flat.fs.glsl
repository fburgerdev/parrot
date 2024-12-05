#version 330 core
// out
out vec4 o_frag_color; 
// in
in vec2 v_tex_coords;
in float v_intensity;

// uniform
uniform sampler2D u_texture;
uniform vec3 u_tint = vec3(1, 1, 1);

void main() {
    o_frag_color = vec4(1, 1, 1, 1) * v_intensity + vec4(0.7F, 0.7F, 0.9, 1) * (1 - v_intensity);
}