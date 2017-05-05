#version 430

layout (location = 0) uniform mat4 modelView;	//modelview matrix
layout (location = 1) uniform mat4 projection;	//projection matrix
layout (location = 2) uniform mat4 model;		//model
layout (location = 3) uniform mat4 invModel;

layout (location = 0) in vec3 position;			//vertex attribute: position
layout (location = 1) in vec3 inNormal;			//vertex attribute: normal
layout (location = 2) in vec2 inUV;				//vertex attribute: texcoords
layout (location = 3) in vec3 inTangent;		//vertex attribute: tangent

layout (location = 0) out vec3 outNormal;		//output: normal
layout (location = 1) out vec4 vertexPos;
layout (location = 2) out vec2 outUV;			//output: texcoords
layout (location = 3) out vec3 outTangent;

void main()
{	
	gl_Position = projection * modelView * model * vec4(position, 1.0);
	outNormal = normalize((model * vec4(inNormal, 0.0f)).xyz);
	outTangent = normalize((invModel * vec4(inTangent, 0.0f)).xyz);
	vertexPos = model * vec4(position, 1.0f);
	outUV = inUV;
}