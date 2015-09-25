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

void Light::CalculateLightColor(const Point<float>& point, const Vector3<float>& normal, const Vector3<float>& viewDirection, const Material& material, Color<float>& calculatedColor) const
{
	calculatedColor = Color<float>(0.0f, 0.0f, 0.0f, 1.0f);

	// Calculate the normalized light direction:
	Vector3<> lightDirection = m_directional ? Vector3<>(m_position.x, m_position.y, m_position.z) : m_position - point;
	lightDirection.normalize();

	// Calculate the normalized half vector:
	Vector3<> halfVector = viewDirection.normalizedVector() + lightDirection;
	halfVector.normalize();

	// Calculate diffuse color:
	float diffuseIntensity = fmaxf(0.0f, lightDirection.dot(normal));
	if (-0.00001f < diffuseIntensity && diffuseIntensity < 0.00001f)
		return;

	Color<> diffuseColor = material.diffuseColor * diffuseIntensity;

	// Calculate specular color:
	float specularIntensity = powf(fmaxf(0.0f, halfVector.dot(normal)), material.shininess);
	Color<> specularColor = material.specularColor * specularIntensity;

	calculatedColor = (diffuseColor + specularColor);

	if (!m_directional)
	{
		float distance = (m_position - point).length();
		float attenuation = m_constantAttenuation + m_linearAttenuation * distance + m_quadraticAttenuation * distance * distance;
		calculatedColor = calculatedColor / attenuation;
	}

	calculatedColor = calculatedColor * m_color;
	calculatedColor.alpha = 1.0f;
}

const Point<float>& Light::GetPosition() const
{
	return m_position;
}

bool Light::IsDirectional() const
{
	return m_directional;
}