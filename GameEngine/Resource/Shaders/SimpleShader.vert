#version 450

layout(location = 0) in vec3 posL;
layout(location = 1) in vec3 normalL;
layout(location = 2) in vec4 color;

layout(location = 0) out VertexOut {
	vec4 posH;
	vec3 normalW;
	vec4 color;
} vout;

void main()
{
	vout.posH = vec4(posL, 1.0);
	vout.normalW = normalL;
	vout.color = color;
	gl_Position = vout.posH;
}

