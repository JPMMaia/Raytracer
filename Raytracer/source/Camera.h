#pragma once

#include "Point.h"
#include "Vector3.h"
#include "Quartenion.h"

class Camera
{
public:
	void Initialize(const Point<>& eye, const Point<>& at, const Vector3<>& up);

	const Point<float>& GetPosition() const;
	const Vector3<float>& GetLeftDirection() const;
	const Vector3<float>& GetUpDirection() const;
	const Vector3<float>& GetViewDirection() const;

private:
	Point<float> m_position;
	Vector3<float> m_leftDirection;
	Vector3<float> m_upDirection;
	Vector3<float> m_viewDirection;
};