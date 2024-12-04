#version 330 core
// out
out vec4 frag_color; 
// in
in vec2 v_tex_coords;
in float v_intensity;

// uniform
uniform sampler2D u_texture;
uniform vec3 u_tint;

void main() {
    frag_color = texture2D(u_texture, v_tex_coords) * vec4(vec3(u_tint * v_intensity), 1);
}