//Created for Graphics I and II
//Author: Minsi Chen

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "vector3.h"
#include "matrix4x4.h"
#include <glm\glm\mat4x4.hpp>
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\gtx\transform.hpp>

class Camera
{
	public:
		enum ECameraType
		{
			//Implement camera switching later
			CAM_NORMAL,
			CAM_SHIP
		};

	private:
		glm::mat4x4						m_viewMatrix;				//View Matrix
		glm::mat4x4						m_projectionMatrix;			//Projection Matrix
		Vector3							m_position;					//Position
		Vector3							m_upVector;					//up vector
		Vector3							m_rightVector;				//right vector
		Vector3							m_viewVector;				//view vector
		Vector3							m_lookAt;					//look at position
		Vector3							m_direction;
		ECameraType						m_cameratype;				//Projection time
		float							m_fov;						//vertical field of view in degree
		float							m_aspectRatio;

	public:
	
										Camera();
		virtual							~Camera();

		void							InitCamera();
		void							SetCameraPosition(const Vector3* position);
		inline const Vector3*			GetCameraPosition() const 
		{
			return &m_position;
		}

		void							SetLookAtPoint(const Vector3* lookAt);
		inline const Vector3*			GetCameraDirection() const
		{
			return &m_direction;
		}
		void							SetUpVector(const Vector3* up);
		inline const Vector3*			GetCameraUpVector() const
		{
			return &m_upVector;
		}

		inline ECameraType				GetCameraType()
		{
			return m_cameratype;
		}

		inline void						SetCameraFOV(float fov)
		{
			m_fov = fov;
		}

		inline float					GetCameraFOV()
		{
			return m_fov;
		}

		inline void						SetCameraAspectRatio(float ar)
		{
			m_aspectRatio = ar;
		}

		inline float					GetCameraAspectRatio()
		{
			return m_aspectRatio;
		}

		void							UpdateViewMatrix();

		inline const glm::mat4x4*			GetViewMatrix() const
		{
			return &m_viewMatrix;
		}
		
		inline const glm::mat4x4*			GetProjectionMatrix() const
		{
			return &m_projectionMatrix;
		}

		//TODO: Setup the projection matrix, hint the Matrix4x4 already has a method for setting up a perspective projection matrix
		void							SetProjectionMatrix(float* projection);		//Using glm instead of Matrix4x4 to set this up

		//Camera Movement Functions
		void							StrafeCamera(float amount);
		void							DollyCamera(float amount);
		void							PedCamera(float amount);
		void							RotateCamera(float yaw, float pitch, float roll);
		void							ZoomCamera(float amount);
};

#endif
