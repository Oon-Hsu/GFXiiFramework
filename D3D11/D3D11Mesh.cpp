#include <d3d11_1.h>
#include "D3D11Mesh.h"
#include "D3D11Texture.h"
#include "../Triangle.h"
#include "../OBJFileReader.h"
#include <glm\glm\gtc\matrix_transform.hpp>

D3D11Mesh::D3D11Mesh()
{

}

D3D11Mesh::D3D11Mesh(LPCWSTR filename, D3D11ShaderProgram* shader)
{
	LoadAndBuildMeshFromOBJFile(filename, shader);
}

D3D11Mesh::~D3D11Mesh()
{
	if (m_vertexLayout) m_vertexLayout->Release();

	if (m_vertexBuffer) m_vertexBuffer->Release();
}

void D3D11Mesh::Render()
{
	ID3D11DeviceContext* pContext = m_shader->GetContext();
	ID3D11ShaderResourceView* ptexRv = dynamic_cast<D3D11Texture*>(m_tex)->m_textureRV;

	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;

	pContext->IASetInputLayout(m_vertexLayout);
	pContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pContext->PSSetShaderResources(0, 1, &ptexRv);

	pContext->Draw(m_numtriangles*3, 0);
}

void D3D11Mesh::LoadAndBuildMeshFromOBJFile(LPCWSTR filename, D3D11ShaderProgram* shader)
{
	Triangle* mesh;

	m_numtriangles = importOBJMesh(filename, &mesh);

	m_shader = shader;

	unsigned int offset = sizeof(Vector3);

	D3D11_INPUT_ELEMENT_DESC vertlayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offset, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 2*offset, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	ID3D11Device* pDevice = shader->GetDevice();
	ID3DBlob* pVSBlob = shader->GetVSBlob();

	HRESULT hr = pDevice->CreateInputLayout(vertlayout, ARRAYSIZE(vertlayout), pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &m_vertexLayout);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex)*m_numtriangles*3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = &(mesh[0].m_vertices[0].m_position[0]);

	pDevice->CreateBuffer(&bd, &initData, &m_vertexBuffer);

	delete [] mesh;
}

void D3D11Mesh::Translate(glm::vec3 vec)
{
	m_transform = glm::translate(m_transform, vec);
}

glm::mat4x4 D3D11Mesh::GetTransformationMatrix()
{
	return m_transform;
}

void D3D11Mesh::Rotate(float angle, glm::vec3 vec)
{
	m_transform = glm::rotate(m_transform, glm::radians(angle), vec);
}

void D3D11Mesh::Scale(glm::vec3 vec)
{
	m_transform = glm::scale(m_transform, vec);
}