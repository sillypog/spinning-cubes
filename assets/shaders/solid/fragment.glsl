#version 150

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex0;
uniform sampler2D tex1;

void main(){
	vec4 col0 = texture(tex0, Texcoord);
	vec4 col1 = texture(tex1, Texcoord);
	vec4 texColor = mix(col0, col1, 0.5);

	outColor = texColor * vec4(Color, 1.0);
}
