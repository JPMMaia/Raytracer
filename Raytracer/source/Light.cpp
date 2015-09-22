#include "Light.h"

void Light::Initialize(const Point<float>& position, const Color<float>& color, bool directional, float constantAttenuation, float linearAttenuation, float quadraticAttenuation)
{
	m_position = position;
	m_color = color;
	m_directional = directional;
	m_constantAttenuation = constantAttenuation;
	m_linearAttenuation = linearAttenuation;
	m_quadraticAttenuation = quadraticAttenuation;
}

void Light::CalculateLightColor(const Point<float>& point, const Vector3<float>& normal, const Vector3<float>& viewDirection, const Material & material, Color<float>& calculatedColor) const
{
	// Calculate the normalized light direction:
	Vector3<> lightDirection = m_directional ? Vector3<>(m_position.x, m_position.y, m_position.z) : m_position - point;
	lightDirection.normalize();

	// Calculate the normalized half vector:
	Vector3<> halfVector = viewDirection.normalizedVector() + lightDirection;
	halfVector.normalize();

	// Calculate diffuse color:
	Color<> diffuseColor = material.diffuseColor * fmaxf(0.0f, lightDirection.dot(normal));

	// Calculate specular color:
	Color<> specularColor = material.specularColor * powf(fmaxf(0.0f, halfVector.dot(normal)), material.shininess);

	// TODO Add visibility/shadowing term:
	calculatedColor = diffuseColor + specularColor;
	calculatedColor.alpha = 1.0f;
}

const Point<float>& Light::GetPosition() const
{
	return m_position;
}
