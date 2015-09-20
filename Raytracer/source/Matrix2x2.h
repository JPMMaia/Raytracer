#pragma once

#include "Vector2.h"

typedef unsigned int UINT;

template<class T>
class Matrix2x2
{
public:
	Matrix2x2();
	Matrix2x2(T v00, T v01, T v10, T v11);

	inline T operator()(UINT line, UINT column) const;
	inline T& operator()(UINT line, UINT column);

	Matrix2x2<T> Inverse() const;

private:
	static const UINT s_SIZE = 2;
	T m_matrix[s_SIZE * s_SIZE];
};

template<class T>
inline Matrix2x2<T>::Matrix2x2()
{
}

template<class T>
inline Matrix2x2<T>::Matrix2x2(T v00, T v01, T v10, T v11)
{
	m_matrix[0] = v00;
	m_matrix[1] = v01;
	m_matrix[2] = v10;
	m_matrix[3] = v11;
}

template<class T>
inline T Matrix2x2<T>::operator()(UINT line, UINT column) const
{
	return m_matrix[line * s_SIZE + column];
}

template<class T>
inline T& Matrix2x2<T>::operator()(UINT line, UINT column)
{
	return m_matrix[line * s_SIZE + column];
}

template<class T>
inline Matrix2x2<T> Matrix2x2<T>::Inverse() const
{
	T v00 = m_matrix[0];
	T v01 = m_matrix[1];
	T v10 = m_matrix[2];
	T v11 = m_matrix[3];

	T determinant = v00 * v11 - v01 * v10;

	return Matrix2x2(
		v11 / determinant,
		- v01 / determinant,
		- v10 / determinant,
		v00 / determinant
		);
}

template<class T>
Vector2<T> operator* (const Matrix2x2<T>& matrix, const Vector2<T>& vector)
{
	return Vector2<T>(
		matrix(0, 0) * vector.x + matrix(0, 1) * vector.y,
		matrix(1, 0) * vector.x + matrix(1, 1) * vector.y
		);
}