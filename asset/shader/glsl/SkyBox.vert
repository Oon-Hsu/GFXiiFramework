#version 430

layout (location = 0) uniform mat4 modelview;
layout (location = 1) uniform mat4 projection;
layout (location = 2) uniform mat4 model;
layout (location = 3) uniform vec3 camPosition;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 inUV;

out vec2 outUV;

void main()
{
	gl_Position = (projection * modelview * model * (vec4(position, 1.0f) + vec4(camPosition, 0.0f)));

	outUV = inUV;
}