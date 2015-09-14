#pragma once

typedef unsigned char BYTE;

template<class T = BYTE>
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
		Color<T> color = Color<T>(
			this->red + other.red,
			this->green + other.green,
			this->blue + other.blue,
			this->alpha + other.alpha
			);

		color.FixOverflow(other);

		return color;
	}

	void FixOverflow(const Color<T>& original)
	{
		if (this->red < original.red)
			this->red = 255;
		if (this->green < original.green)
			this->green = 255;
		if (this->blue < original.blue)
			this->blue = 255;
		if (this->alpha < original.alpha)
			this->alpha = 255;
	}
};

template<class T>
inline Color<T> operator*(float scalar, const Color<T>& vector)
{
	Color<T> color = Color<T>(
		scalar * vector.red,
		scalar * vector.green,
		scalar * vector.blue,
		scalar * vector.alpha
		);

	color.FixOverflow(vector);

	return color;
}
template<class T>
inline Color<T> operator*(const Color<T>& vector, float scalar)
{
	return scalar * vector;
}