#pragma once

#include <Windows.h>
#include "../Renderable.h"
#include "../Triangle.h"
#include "D3D11Shader.h"
#include <glm\glm\vec2.hpp>
#include <glm\glm\vec3.hpp>

class D3D11Mesh :	public Renderable
{
	private: 
		D3D11ShaderProgram*			m_shader;
		ID3D11InputLayout*			m_vertexLayout;
		ID3D11Buffer*				m_vertexBuffer;
		ID3D11Buffer*				m_indexBuffer;
		int							m_numtriangles;

	public:
		D3D11Mesh();
		D3D11Mesh(LPCWSTR filename, D3D11ShaderProgram* shader);
		~D3D11Mesh();

		void LoadAndBuildMeshFromOBJFile(LPCWSTR filename, D3D11ShaderProgram* shader);

		void Render();
		glm::mat4x4	GetTransformationMatrix();
		void Translate(glm::vec3 vec);
		void Rotate(float angle, glm::vec3 vec);
		void Scale(glm::vec3 vec);
};

