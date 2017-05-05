#pragma once

#include "BaseTexture.h"
#include <glm\glm\vec3.hpp>
#include <glm\glm\mat4x4.hpp>
#include "Vector3.h"

//This is an abstract class
//It cannot be instantiated without being inherited by a concrete class
class Renderable
{
	protected:
		BaseTexture				*m_tex;
		BaseTexture				*m_spec;
		BaseTexture				*m_norm;
		glm::mat4x4				m_transform = glm::mat4x4(1.0f);
	public:

		//this is a pure virtual function
								Renderable() { m_tex = 0; }
		virtual void			Render() = 0;
		
		inline void				SetTexture( BaseTexture *tex )
		{
			m_tex = tex;
		}

		inline void	SetSpecular(BaseTexture *spec)
		{
			m_spec = spec;
		}

		inline void SetNormalMap(BaseTexture *norm)
		{
			m_norm = norm;
		}

		virtual glm::mat4x4 GetTransformationMatrix() = 0;
		virtual void Translate(glm::vec3 vec) = 0;
		virtual void Rotate(float angle, glm::vec3 vec) = 0;
		virtual void Scale(glm::vec3 vec) = 0;
};