#pragma once

#include "OpenGL\OGLTexture.h"
#include "Renderable.h"
#include <glm/glm/vec3.hpp>
#include <glm/glm/mat4x4.hpp>

class SkyBox : public Renderable
{
private:
	OGLTexture *m_texture[6];
	unsigned int m_vao;
	unsigned int m_vbo_verts;
	unsigned int m_vbo_indices;

private:
	struct SkyboxVertex
	{
		float position[3];
		float uv[2];
	};

public:
	SkyBox();
	~SkyBox();

	void Init();
	void Render();
	void LoadTextures();
	void SetVertices();

	glm::mat4x4	GetTransformationMatrix();

	//No function but necessary because of abstraction
	inline void Rotate(float angle, glm::vec3 vec)
	{
		return;
	}

	inline void Translate(glm::vec3 vec)
	{
		return;
	}

	inline void Scale(glm::vec3 vec)
	{
		return;
	}
};