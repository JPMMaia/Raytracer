#pragma once

#include "Point.h"
#include "Color.h"
#include "Material.h"

struct PointLight
{
	Point<> position;
	Color<> color;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;

	PointLight()
	{
	}
	PointLight(const Point<>& position, const Color<>& color) : 
		position(position), color(color), 
		constantAttenuation(1.0f), linearAttenuation(0.1f), quadraticAttenuation(0.01f)
	{
	}
	PointLight(const Point<>& position, const Color<>& color, float constantAttenuation, float linearAttenuation, float quadraticAttenuation) :
		position(position), color(color),
		constantAttenuation(constantAttenuation), linearAttenuation(linearAttenuation), quadraticAttenuation(quadraticAttenuation)
	{
	}

	inline void CalculateLightColor(const Point<>& point, const Vector<>& normal, const Vector<>& viewDirection, const Material& material, Color<>& calculatedColor) const
	{
		// Calculate the normalized light direction:
		Vector<> lightDirection = this->position - point;
		lightDirection.normalize();

		// Calculate the normalized half vector:
		Vector<> halfVector = viewDirection + lightDirection;
		halfVector.normalize();

		// Calculate diffuse color:
		Color<> diffuseColor = material.diffuseColor * fmaxf(0.0f, lightDirection.dot(normal));

		// Calculate specular color:
		Color<> specularColor = material.specularColor * powf(fmaxf(0.0f, halfVector.dot(normal)), material.shininess);

		// TODO Add visibility/shadowing term:
		calculatedColor = diffuseColor + specularColor;
	}
};