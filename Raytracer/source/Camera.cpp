#include "Camera.h"

void Camera::Initialize(const Point<>& eye, const Point<>& at, const Vector3<>& up)
{
	Vector3<> upDirection = up.normalizedVector();

	Vector3<> viewDirection = at - eye;
	viewDirection.normalize();
	
	Vector3<> rightDirection = upDirection.cross(viewDirection);

	m_translation = eye;
}

void Camera::Update()
{
	if (m_dirty)
	{
		

		m_dirty = false;
	}
}

const Point<float>& Camera::GetPosition() const
{
	return m_position;
}

void Camera::SetTranslation(const Point<float>& translation)
{
	m_translation = translation;
	m_dirty = true;
}