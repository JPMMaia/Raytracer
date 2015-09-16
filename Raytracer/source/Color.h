#pragma once

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

	inline Color<T> operator+(const Color<T>& other) const
	{
		return Color<T>(
			this->red + other.red,
			this->green + other.green,
			this->blue + other.blue,
			this->alpha + other.alpha
			);
	}
};

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