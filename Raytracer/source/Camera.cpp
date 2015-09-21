#include "Camera.h"
#include "Constants.h"

void Camera::Initialize(const Point<>& eye, const Point<>& at, const Vector3<>& up)
{
	m_position = eye;

	m_viewDirection = at - eye;
	m_viewDirection.normalize();
	
	m_leftDirection = up.cross(m_viewDirection);
	m_leftDirection.normalize();

	m_upDirection = m_viewDirection.cross(m_leftDirection);
}

const Point<float>& Camera::GetPosition() const
{
	return m_position;
}

const Vector3<float>& Camera::GetLeftDirection() const
{
	return m_leftDirection;
}

const Vector3<float>& Camera::GetUpDirection() const
{
	return m_upDirection;
}

const Vector3<float>& Camera::GetViewDirection() const
{
	return m_viewDirection;
}