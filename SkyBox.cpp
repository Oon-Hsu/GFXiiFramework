#include "SkyBox.h"
#include <Windows.h>
#include "GLEW/include/glew.h"

SkyBox::SkyBox()
{
	Init();
}

SkyBox::~SkyBox()
{
	delete m_texture;
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo_verts);
	glDeleteBuffers(1, &m_vbo_indices);
}

void SkyBox::Init()
{
	LoadTextures();
	SetVertices();
}

void SkyBox::Render()
{
	unsigned int texHandle = dynamic_cast<OGLTexture*>(m_tex)->m_syshandle;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texHandle);

	glBindVertexArray(m_vao);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void SkyBox::LoadTextures()
{
	m_texture[0] = new OGLTexture();
	m_texture[0]->CreateTextureFromFile("../asset/sky_textures/sky_ft.tga");

	m_texture[1] = new OGLTexture();
	m_texture[1]->CreateTextureFromFile("../asset/sky_textures/sky_bk.tga");

	m_texture[2] = new OGLTexture();
	m_texture[2]->CreateTextureFromFile("../asset/sky_textures/sky_lt.tga");

	m_texture[3] = new OGLTexture();
	m_texture[3]->CreateTextureFromFile("../asset/sky_textures/sky_rt.tga");

	m_texture[4] = new OGLTexture();
	m_texture[4]->CreateTextureFromFile("../asset/sky_textures/sky_tp.tga");

	m_texture[5] = new OGLTexture();
	m_texture[5]->CreateTextureFromFile("../asset/sky_textures/sky_bt.tga");

	SetTexture(*m_texture);
}	

void SkyBox::SetVertices()
{
	SkyboxVertex corners[] =
	{
		//Back
		{ -20.0f, -20.0f, 20.0f, 0.75f, 1.0f / 3.0f },
		{ 20.0f, -20.0f, 20.0f, 1.0f, 1.0f / 3.0f },
		{ 20.0f, 20.0f, 20.0f, 1.0f, 2.0f / 3.0f },
		{ -20.0f, 20.0f, 20.0f, 0.75f, 2.0f / 3.0f },

		//Left
		{ 20.0f, -20.0f, 20.0f, 0.0f, 1.0f / 3.0f },
		{ 20.0f, -20.0f, -20.0f, 0.25f, 1.0f / 3.0f },
		{ 20.0f, 20.0f, -20.0f, 0.25f, 2.0f / 3.0f },
		{ 20.0f, 20.0f, 20.0f, 0.0f, 2.0f / 3.0f },

		//Front
		{ 20.0f, -20.0f, -20.0f, 0.25f, 1.0f / 3.0f },
		{ -20.0f, -20.0f, -20.0f, 0.5f, 1.0f / 3.0f },
		{ -20.0f, 20.0f, -20.0f, 0.5f, 2.0f / 3.0f },
		{ 20.0f, 20.0f, -20.0f, 0.25f, 2.0f / 3.0f },

		//Right
		{ -20.0f, -20.0f, -20.0f, 0.5f, 1.0f / 3.0f },
		{ -20.0f, -20.0f, 20.0f, 0.75f, 1.0f / 3.0f },
		{ -20.0f, 20.0f, 20.0f, 0.75f, 2.0f / 3.0f },
		{ -20.0f, 20.0f, -20.0f, 0.5f, 2.0f / 3.0f },

		//Top
		{ -20.0f, 20.0f, 20.0f, 0.5f, 1.0f },
		{ 20.0f, 20.0f, 20.0f, 0.25f, 1.0f },
		{ 20.0f, 20.0f, -20.0f, 0.25f, 2.0f / 3.0f },
		{ -20.0f, 20.0f, -20.0f, 0.5f, 2.0f / 3.0f },

		//Bottom
		{ -20.0f, -20.0f, -20.0f, 0.5f, 1.0f / 3.0f },
		{ 20.0f, -20.0f, -20.0f, 0.25f, 1.0f / 3.0f },
		{ 20.0f, -20.0f, 20.0f, 0.25f, 0.0f },
		{ -20.0f, -20.0f, 20.0f, 0.5f, 0.0f }
	};

	unsigned int indices[] =
	{
		3, 1, 0,
		3, 2, 1,

		7, 5, 4,
		7, 6, 5,

		11, 9, 8,
		11, 10, 9,

		15, 14, 12,
		14, 13, 12,

		19, 18, 16,
		18, 17, 16,

		23, 22, 20,
		22, 21, 20
	};

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo_verts);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_verts);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(SkyboxVertex), &corners[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SkyboxVertex), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SkyboxVertex), (void*)(NULL + 12));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &m_vbo_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(int), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

glm::mat4x4 SkyBox::GetTransformationMatrix()
{
	return m_transform;
}
