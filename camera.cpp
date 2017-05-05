//Created for Graphics I and II
//Author: Minsi Chen

#include "camera.h"
#include "Matrix4x4.h"
#include "Vector4.h"
#include "quaternion.h"
#include <math.h>

Camera::Camera()
{
	InitCamera();
}

Camera::~Camera()
{
}

void Camera::InitCamera()
{
	//Desired initial camera position
	m_position.SetVector(0.0f, 5.0f, 100.0f);
	m_upVector.SetVector(0.0f, 1.0f, 0.0f);
	m_direction.SetVector(0.0f, 0.0, -1.0f);
	m_rightVector = m_direction.CrossProduct(m_upVector);
	m_upVector = m_rightVector.CrossProduct(m_direction);
	UpdateViewMatrix();
}

void Camera::SetCameraPosition(const Vector3* position)
{
	m_position = (*position);
	UpdateViewMatrix();
}

void Camera::SetLookAtPoint(const Vector3* lookAt)
{
	//TODO: Gram-Schmidt orthogonalisation algorithm can be used for this
	//force a 90 degree angle between the 3 vectors to correct any unwanted flaws in their direction
	//come back to this later since this seems to be "extra fluff"
	m_direction = (*lookAt) - m_position;
	m_direction.Normalise();

	m_rightVector = m_direction.CrossProduct(m_upVector);
	m_upVector = m_rightVector.CrossProduct(m_direction);

	m_rightVector.Normalise();
	m_upVector.Normalise();

	UpdateViewMatrix();
}

void Camera::SetUpVector(const Vector3* up)
{
	m_upVector = (*up);
	
	m_rightVector = m_direction.CrossProduct(m_upVector);
	m_upVector = m_rightVector.CrossProduct(m_direction);

	m_rightVector.Normalise();
	m_upVector.Normalise();

	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	glm::vec3 position, direction, up;

	position[0] = m_position[0];
	position[1] = m_position[1];
	position[2] = m_position[2];
	direction[0] = m_direction[0];
	direction[1] = m_direction[1];
	direction[2] = m_direction[2];
	up[0] = m_upVector[0];
	up[1] = m_upVector[1];
	up[2] = m_upVector[2];

	m_viewMatrix = glm::lookAt(position, (position + direction), up);
}

void Camera::SetProjectionMatrix(float* projection)
{
	m_projectionMatrix = glm::make_mat4x4(projection);
}

void Camera::StrafeCamera(float amount)
{
	m_position = m_position + (m_rightVector * amount);
	SetCameraPosition(&m_position);
}

void Camera::DollyCamera(float amount)
{
	m_position = m_position + (m_direction * amount);
	SetCameraPosition(&m_position);
}

void Camera::PedCamera(float amount)
{
	m_position = m_position + (m_upVector * amount);
	SetCameraPosition(&m_position);
}

void Camera::RotateCamera(float yaw, float pitch, float roll)
{
	Quaternion yawQ, pitchQ, rollQ, yawC, pitchC, rollC, upQ, directionQ;

	//Set the quaternions
	yawQ.SetQuaternion(m_upVector * sin(yaw * 0.5), cos(yaw * 0.5));
	pitchQ.SetQuaternion(m_rightVector * sin(pitch * 0.5), cos(pitch * 0.5));
	rollQ.SetQuaternion(m_direction * sin(roll * 0.5), cos(roll * 0.5));
	
	//Set the conjugates by changing the polarity of the Vector portion
	yawC.SetQuaternion(yawQ.GetVector() * -1, yawQ.GetScalar());
	pitchC.SetQuaternion(pitchQ.GetVector() * -1, pitchQ.GetScalar());
	rollC.SetQuaternion(rollQ.GetVector() * -1, rollQ.GetScalar());
	
	//Recompute up, direction, and view vectors
	upQ.SetQuaternion(m_upVector, 0);
	directionQ.SetQuaternion(m_direction, 0);
	upQ = rollQ * upQ* rollC;
	directionQ = (pitchQ * directionQ * pitchC) + (yawQ * directionQ * yawC);

	m_upVector = upQ.GetVector();
	m_direction = directionQ.GetVector();
	m_upVector.Normalise();
	m_direction.Normalise();
	m_rightVector = m_direction.CrossProduct(m_upVector);

	UpdateViewMatrix();
}

void Camera::ZoomCamera(float amount)
{
	//Prevent fov from inverting and keep proportions relatively constant
	if ((m_fov + amount) < 70.5f && (m_fov + amount) > 69.5f)
	{
		m_fov = m_fov + amount;
	}
	glm::mat4x4 projection = glm::perspective(GetCameraFOV(), GetCameraAspectRatio(), 1.0f, 1000.0f);
	SetProjectionMatrix(&projection[0][0]);
}
