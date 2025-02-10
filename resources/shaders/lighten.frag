#ifdef GL_ES
precision mediump float;
#endif
 
uniform sampler2D u_texture;
uniform vec2 u_tex_coord;

void main() {
	vec4 to_color = texture2D(u_texture, u_tex_coord);
	to_color.b = 1.0;
	gl_FragColor = to_color;
}