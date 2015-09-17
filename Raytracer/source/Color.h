#pragma once

#include <math.h>

typedef unsigned char BYTE;

template<class T = float>
struct Color
{
	T red;
	T green;
	T blue;
	T alpha;

	Color<T>()
	{
	}
	Color<T>(T red, T green, T blue, T alpha) : red(red), green(green), blue(blue), alpha(alpha)
	{
	}

	template<class TypeToCast>
	inline operator Color<TypeToCast>() const;
};

template<class T>
template<class TypeToCast>
inline Color<T>::operator Color<TypeToCast>() const
{
	return Color<TypeToCast>(
		this->red,
		this->green,
		this->blue,
		this->alpha
		);
}

template<>
template<>
inline Color<BYTE>::operator Color<float>() const
{
	return Color<float>(
		static_cast<float>(this->red) / 255.0f,
		static_cast<float>(this->green) / 255.0f,
		static_cast<float>(this->blue) / 255.0f,
		static_cast<float>(this->alpha) / 255.0f
		);
}

template<>
template<>
inline Color<float>::operator Color<BYTE>() const
{
	return Color<BYTE>(
		static_cast<BYTE>(this->red * 255.0f),
		static_cast<BYTE>(this->green * 255.0f),
		static_cast<BYTE>(this->blue * 255.0f),
		static_cast<BYTE>(this->alpha * 255.0f)
		);
}

template<class T>
inline Color<T> operator+(const Color<T>& color1, const Color<T>& color2)
{
	return Color<T>(
		color1.red + color2.red,
		color1.green + color2.green,
		color1.blue + color2.blue,
		color1.alpha + color2.alpha
		);
}

template<class T>
inline Color<T> operator*(float scalar, const Color<T>& vector)
{
	return Color<T>(
		scalar * vector.red,
		scalar * vector.green,
		scalar * vector.blue,
		scalar * vector.alpha
		);
}
template<class T>
inline Color<T> operator*(const Color<T>& vector, float scalar)
{
	return scalar * vector;
}