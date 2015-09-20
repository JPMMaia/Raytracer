#pragma once

#include "Color.h"

struct Material
{
	Color<float> ambientColor;
	Color<float> emissionColor;
	Color<float> diffuseColor;
	Color<float> specularColor;
	float shininess;

	Material()
	{
		this->ambientColor.alpha = 1.0f;
		this->emissionColor.alpha = 1.0f;
		this->diffuseColor.alpha = 1.0f;
		this->specularColor.alpha = 1.0f;
	}
	Material(const Color<float>& ambientColor, const Color<float>& diffuseColor, const Color<float>& specularColor, float shininess) :
		ambientColor(ambientColor),
		diffuseColor(diffuseColor), 
		specularColor(specularColor), 
		shininess(shininess),
		emissionColor(0, 0, 0, 0)
	{
	}
};