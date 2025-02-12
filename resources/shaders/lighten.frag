#version 110

varying vec2 fragTexCoord;
varying vec2 texPosition;
uniform sampler2D palette;
uniform sampler2D texture;
uniform float u_key;
uniform float u_size;
uniform vec2 u_mask_1;
uniform vec2 u_mask_2;
uniform vec2 u_mask_3;
uniform vec2 u_offset;

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

vec4 saturateColor(vec4 inputColor, float saturationAmount) {
    // Convert the color to grayscale using a luminance formula
    float gray = dot(inputColor.rgb, vec3(0.2126, 0.7152, 0.0722)); // Using standard luminance weights

    // Blend between the grayscale color and the original color based on the saturation amount
    vec3 saturatedColor = mix(vec3(gray), inputColor.rgb, saturationAmount);

    // Ensure that the result is within the valid range [0.0, 1.0]
    return vec4(clamp(saturatedColor, 0.0, 1.0), inputColor.a);
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
	float u_px = float(2.0);
    vec2 pixelPoint = gl_FragCoord.xy;
    pixelPoint = floor(pixelPoint / u_px) * u_px;
	if (isPointInConvexPolygon(pixelPoint)) { shift(u_key); }
	if (isPointInConvexPolygon(pixelPoint) && !isPointInConvexPolygon(pixelPoint + vec2(2.0, 2.0))) { pixel = saturateColor(pixel, 2.0); } 
	if (isPointInConvexPolygon(pixelPoint) && !isPointInConvexPolygon(pixelPoint + vec2(8.0, 8.0))) { pixel = saturateColor(pixel, 1.5); } 
	gl_FragColor = gl_Color * pixel;

	// multiply it by the color
}