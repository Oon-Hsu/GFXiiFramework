#version 430

layout (binding = 0) uniform sampler2D texColour;
layout (binding = 1) uniform sampler2D texNormal;
layout (binding = 2) uniform sampler2D texSpec;
layout (binding = 3) uniform sampler2D texEnv;
layout (binding = 4) uniform sampler2D shadowmap;

layout (location = 0) in vec3 outNormal;
layout (location = 1) in vec4 vertexPos;
layout (location = 2) in vec2 outUV;
layout (location = 3) in vec3 outTangent; 

layout (location = 0) out vec4 outFrag;

vec4 viewvec;
vec4 basecolour = texture(texColour, outUV);
uniform float specPower;
uniform vec3 cam_Pos;

uniform struct DirectionalLight
{
    vec3 colour;
    float diffuseIntensity;
    vec3 direction;
} dirLight;

vec3 CalculateNormalMap()
{
	vec3 normal, calcNormal, tangent, bitangent, bumpMapNormal, bumpOffset;
	bumpOffset = vec3(0.5f);
	
	calcNormal = normalize(outNormal);

	tangent = normalize(outTangent);
	tangent = normalize(tangent - dot(tangent, calcNormal) * calcNormal);

	bitangent = cross(tangent, calcNormal);

	bumpMapNormal = 2 * ((texture(texNormal, outUV).xyz) - bumpOffset);

	mat3 TBNmatrix = mat3(tangent, bitangent, calcNormal);

	normal = normalize(TBNmatrix * bumpMapNormal);

	return normal;
}

vec4 CalculateLight(vec4 colour, float diffuseIntensity, vec4 direction, vec4 normal)
{
    float lambertFactor = max(0.0, dot(-direction, normal));

    vec4 specularMap = texture(texSpec, outUV);

    vec4 diffuse = vec4(0.0);
    vec4 specular = vec4(0.0);

    if(lambertFactor > 0.0f)
    {
        specular = vec4(1.0f);
        diffuse = colour * diffuseIntensity * lambertFactor * basecolour;

        vec4 reflection = reflect(direction, normal);

        float angle = pow(max(0.0, dot(viewvec, reflection)), specPower);

        specular = specularMap * angle;
    }
    return (diffuse + specular);
}

vec4 CalcDirLight(vec4 normal)
{
    return CalculateLight(vec4(dirLight.colour, 1.0f), dirLight.diffuseIntensity, vec4(dirLight.direction, 0.0f), normal);
}

void main()
{
    viewvec = vec4(normalize(vec4(cam_Pos, 1.0f) - vertexPos).xyz, 0.0f);
	
    vec4 ambient = basecolour * 0.3f;
	
	vec4 normal = vec4(CalculateNormalMap(), 0.0);
    vec4 light = ambient + CalcDirLight(normal);

    outFrag = light;
}
