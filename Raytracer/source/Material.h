#pragma once

#include "Color.h"

struct Material
{
	Color<> emissionColor;
	Color<> diffuseColor;
	Color<> specularColor;
	float shininess;

	Material()
	{
	}
	Material(const Color<>& diffuseColor, const Color<>& specularColor, float shininess) :
		diffuseColor(diffuseColor), 
		specularColor(specularColor), 
		shininess(shininess),
		emissionColor(0, 0, 0, 0)
	{
	}
};