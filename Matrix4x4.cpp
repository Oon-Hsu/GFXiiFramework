//No longer using this class but work was put into it so I'll leave it in the source code anyway

#include <memory.h>
#include <math.h>
#include "Vector4.h"
#include "Matrix4x4.h"

#define PI_DIV_180 0.01745329251994329576923690768489f

Matrix4x4::Matrix4x4()
{
	SetIdentity();
}

Matrix4x4::Matrix4x4(const Matrix4x4& rhs)
{
	size_t matrix_size = sizeof(m_element);

	memcpy_s((&m_element[0][0]), matrix_size, rhs.ToPtr(), matrix_size);
}

Matrix4x4::~Matrix4x4()
{

}

const float* Matrix4x4::ToPtr() const
{
	return &(m_element[0][0]);
}

void Matrix4x4::SetZero()
{
	memset(&m_element, 0, sizeof(m_element));
}

void Matrix4x4::SetIdentity()
{
	SetZero();
	m_element[0][0] = m_element[1][1] = m_element[2][2] = m_element[3][3] = 1.0f;
}

Matrix4x4 Matrix4x4::operator* (const Matrix4x4& rhs) const
{
	//TODO: Implement Matrix-Matrix Multiplcation

	Matrix4x4 result;
	
	for (int r = 0; r < 4; r++)
		for (int c = 0; c < 4; c++)
			result.m_element[r][c] = m_element[r][0] * rhs.m_element[0][c] 
								   + m_element[r][1] * rhs.m_element[1][c] 
								   + m_element[r][2] * rhs.m_element[2][c] 
								   + m_element[r][3] * rhs.m_element[3][c];

	return result;
}

Vector4 Matrix4x4::operator* (const Vector4& rhs) const
{
	Vector4 result;

	result = rhs;
	
	//TODO: Implement Matrix-Vector Multiplcation
	for (int r = 0; r < 4; r++)
		result[r] = m_element[r][0] * rhs[0]
				  + m_element[r][1] * rhs[1]
				  + m_element[r][2] * rhs[2]
				  + m_element[r][3] * rhs[3];

	return result;
}

void Matrix4x4::SetRotationXAxis(float degrees)
{
	SetIdentity();

	float radian = degrees*PI_DIV_180;

	m_element[1][1] = cosf(radian);
	m_element[1][2] = -sinf(radian);
	m_element[2][1] = sinf(radian);
	m_element[2][2] = cosf(radian);
}

void Matrix4x4::SetRotationYAxis(float degrees)
{
	SetIdentity();

	float radian = degrees*PI_DIV_180;

	m_element[0][0] = cosf(radian);
	m_element[0][2] = sinf(radian);
	m_element[2][0] = -sinf(radian);
	m_element[2][2] = cosf(radian);

}

void Matrix4x4::SetRotationZAxis(float degrees)
{
	SetIdentity();

	float radian = degrees*PI_DIV_180;

	m_element[0][0] = cosf(radian);
	m_element[0][1] = -sinf(radian);
	m_element[1][0] = sinf(radian);
	m_element[1][1] = cosf(radian);
}

void Matrix4x4::SetTranslate(const Vector4& tvec)
{
	SetIdentity();

	//TODO: Set this matrix as a translation matrix given the translation vector tvec
	m_element[0][3] = tvec[0];
	m_element[1][3] = tvec[1];
	m_element[2][3] = tvec[2];
	m_element[3][3] = tvec[3];
}

void Matrix4x4::SetScale(float sx, float sy, float sz)
{
	SetZero();

	//TODO: Set this matrix as a scaling matrix given the scaling factors sx, sy, sz
	m_element[0][0] = sx;
	m_element[1][1] = sy;
	m_element[2][2] = sz;
	m_element[3][3] = 1.0;
}

void Matrix4x4::SetPerspective(float fovy, float aspect_ratio, float zNear, float zFar)
{
	float radian = fovy*PI_DIV_180;
	float tan_fovy = tanf(radian*0.5f);

	SetZero();

	m_element[0][0] = 1.0f / (aspect_ratio*tan_fovy);
	m_element[1][1] = 1.0f / tan_fovy;
	m_element[2][2] = -(zFar + zNear) / (zFar - zNear);
	m_element[2][3] = -1.0f;
	m_element[3][2] = -(2.0f*zFar*zNear) / (zFar - zNear);
}

void Matrix4x4::SetViewMatrix(const Vector4& camera_position, const Vector4& view_vector, const Vector4& up_vector)
{
	//Using glm::mat4x4 instead
	Vector4 v = view_vector - camera_position;
	Vector4 r = v * up_vector;
	Vector4 u = r * v;

	for (int c = 0; c < 4; c++)
	{
		if (c == 3)
		{
			m_element[0][c] = m_element[1][c] = m_element[2][c] = 0.0;
			m_element[3][c] = 1.0;
		}
		else
		{
			m_element[0][c] = r[c];
			m_element[1][c] = u[c];
			m_element[2][c] = v[c];
			m_element[3][c] = camera_position[c];
		}
	}
}
