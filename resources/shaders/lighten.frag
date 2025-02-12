#version 110

varying vec2 fragTexCoord;
uniform sampler2D palette;
uniform sampler2D texture;
uniform float u_key;
uniform float u_size;
uniform vec2 u_mask_1;
uniform vec2 u_mask_2;
uniform vec2 u_mask_3;

vec4 source = texture2D(texture, fragTexCoord);
vec4 pixel = texture2D(texture, fragTexCoord);

float cross2D(vec2 a, vec2 b) { return a.x * b.y - a.y * b.x; }

void shift(float amount) {
	int i_size = int(u_size);
	for (int i = 0; i < i_size; i++) {
		float fi = float(i);
		vec4 swatch = texture2D(palette, vec2(fi / u_size, 0));
		vec4 next = texture2D(palette, vec2((fi + amount) / u_size, 0));
		if (source.rgb == swatch.rgb) { pixel.rgb = next.rgb; }
	}
}

bool isPointInConvexPolygon(vec2 point) {
	bool inside = true;
	for (int i = 0; i < 3; i++) {
		vec2 v1, v2;
		if (i == 0) {
			v1 = u_mask_1;
			v2 = u_mask_2;
		}
		if (i == 1) {
			v1 = u_mask_2;
			v2 = u_mask_3;
		}
		if (i == 2) {
			v1 = u_mask_3;
			v2 = u_mask_1;
		}

		vec2 edge = v2 - v1;
		vec2 toPoint = point - v1;

		if (cross2D(edge, toPoint) < 0.0) {
			inside = false;
			break;
		}
	}
	return inside;
}

void main() {
	if (isPointInConvexPolygon(gl_FragCoord.xy)) { shift(u_key); }
	gl_FragColor = gl_Color * pixel;

	// multiply it by the color
}