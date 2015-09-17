#pragma once

#include "Point.h"
#include "Vector.h"
#include "Quartenion.h"

class Camera
{
public:
	void Initialize(const Point<>& eye, const Point<>& at, const Vector<>& up);

	void Update();

	const Point<float>& GetPosition() const;
	void SetTranslation(const Point<>& translation);

private:
	Point<float> m_position;
	bool m_dirty;

	Point<float> m_translation;
	Quartenion m_rotation;
};