#version 450

layout(location = 0) in VertexOut {
	vec4 posH;
	vec3 normalW;
	vec4 color;
} pin;

layout(location = 0) out vec4 fragColor;

void main()
{
	fragColor = pin.color;
}
