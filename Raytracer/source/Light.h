#pragma once

#include "Color.h"
#include "Material.h"
#include "Point.h"

class Light
{
public:
	void Initialize(const Point<float>& position, const Color<float>& color, bool directional, float constantAttenuation = 1.0f, float linearAttenuation = 0.1f, float quadraticAttenuation = 0.01f);
	void CalculateLightColor(const Point<float>& point, const Vector3<float>& normal, const Vector3<float>& viewDirection, const Material& material, Color<float>& calculatedColor) const;

	const Point<float>& GetPosition() const;
	bool IsDirectional() const;

private:
	Point<float> m_position;
	Color<> m_color;
	float m_constantAttenuation;
	float m_linearAttenuation;
	float m_quadraticAttenuation;
	bool m_directional;
};