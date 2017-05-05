#include <Windows.h>
#include "OGLMesh.h"
#include "../Triangle.h"
#include "../OBJFileReader.h"
#include "OGLTexture.h"
#include "GLEW/include/glew.h"
#include <glm\glm\gtc\matrix_transform.hpp>

OGLMesh::OGLMesh()
{

}

OGLMesh::OGLMesh(LPCWSTR filename)
{
	LoadAndBuildMeshFromOBJFile(filename);
}

OGLMesh::~OGLMesh()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo_verts);
}

void OGLMesh::Render()
{
	unsigned int texHandle = dynamic_cast<OGLTexture*>(m_tex)->m_syshandle;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texHandle);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_verts);
	glDrawArrays(GL_TRIANGLES, 0, m_numtriangles*3);

	glBindVertexArray(0);
}

void OGLMesh::LoadAndBuildMeshFromOBJFile(LPCWSTR filename)
{
	Triangle* mesh;

	m_numtriangles = importOBJMesh(filename, &mesh);
	
	int offset = sizeof(Vector3);
	int stride = sizeof(Vertex);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo_verts);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_verts);
	glBufferData(GL_ARRAY_BUFFER, 3 * m_numtriangles * sizeof(Vertex), &(mesh[0].m_vertices[0].m_position[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(NULL + offset));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(NULL + 2*offset));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(NULL + 3 * offset));
	glEnableVertexAttribArray(3);
			
	glBindVertexArray(0);

	delete[] mesh;
}

void OGLMesh::Translate(glm::vec3 vec)
{
	m_transform = glm::translate(m_transform, vec);
}

void OGLMesh::Rotate(float angle, glm::vec3 vector)
{
	m_transform = glm::rotate(m_transform, glm::radians(angle), vector);
}

glm::mat4x4 OGLMesh::GetTransformationMatrix()
{
	return m_transform;
}

void OGLMesh::Scale(glm::vec3 vec)
{
	m_transform = glm::scale(m_transform, vec);
}