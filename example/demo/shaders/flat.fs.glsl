#version 330 core
// out
out vec4 o_frag_color; 
// in
in vec3 v_position;
in vec3 v_normal;
in vec2 v_tex_coords;

// uniform
uniform sampler2D u_texture;
uniform vec3 u_tint = vec3(1, 1, 1);

void main() {
    vec3 color = applyLighting(texture(u_texture, v_tex_coords).rgb, v_position, v_normal);
    o_frag_color = vec4(color, 1);
}