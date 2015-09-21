#include "Quartenion.h"

Quartenion::Quartenion()
{
}
Quartenion::Quartenion(float w, float x, float y, float z)
	: w(w),	x(x), y(y), z(z)
{
}

Quartenion Quartenion::Conjugate() const
{
	return Quartenion(w, -x, -y, -z);
}
float Quartenion::Norm() const
{
	return sqrtf(NormSquared());
}
float Quartenion::NormSquared() const
{
	return w*w + x*x + y*y + z*z;
}
Quartenion& Quartenion::Normalize()
{
	float norm = Norm();

	*this /= norm;

	return *this;
}
Quartenion Quartenion::Inverse() const
{
	return Conjugate() / NormSquared();
}

Quartenion Quartenion::operator+(const Quartenion & other) const
{
	Quartenion output(*this);

	output.w = this->w + other.w;
	output.x = this->x + other.x;
	output.y = this->y + other.y;
	output.z = this->z + other.z;

	return output;
}
Quartenion Quartenion::operator*(const Quartenion & other) const
{
	Quartenion output(*this);

	output.w = w*other.w - x*other.x - y*other.y - z*other.z;
	output.x = w*other.x + x*other.w + y*other.z - z*other.y;
	output.y = w*other.y + y*other.w + z*other.x - x*other.z;
	output.z = w*other.z + z*other.w + x*other.y - y*other.x;

	return output;
}
Quartenion& Quartenion::operator+=(const Quartenion& other)
{
	*this = *this + other;

	return *this;
}
Quartenion& Quartenion::operator*=(const Quartenion & other)
{
	*this = *this * other;

	return *this;
}

Quartenion Quartenion::operator*(float value) const
{
	return Quartenion(
		this->w * value,
		this->x * value,
		this->y * value,
		this->z * value
		);
}
Quartenion Quartenion::operator/(float value) const
{
	return Quartenion(
		this->w / value,
		this->x / value,
		this->y / value,
		this->z / value
		);
}
Quartenion& Quartenion::operator*=(float value)
{
	*this = *this * value;

	return *this;
}
Quartenion & Quartenion::operator/=(float value)
{
	*this = *this / value;

	return *this;
}

Vector3<float> Quartenion::Rotate(const Vector3<float>& vector, const Quartenion & rotateQuartenion)
{
	Quartenion result = rotateQuartenion * Quartenion(0.0f, vector.x, vector.y, vector.z) * rotateQuartenion.Conjugate();

	return Vector3<float>(result.x, result.y, result.z);
}

Vector3<float> Quartenion::Rotate(const Vector3<float>& vector, const Vector3<float>& axis, float angle)
{
	Quartenion rotateQuartenion = Quartenion::FromAxisAngle(axis, angle);

	return Quartenion::Rotate(vector, rotateQuartenion);
}

Quartenion Quartenion::FromAxisAngle(const Vector3<float>& axis, float angle)
{
	Quartenion quartenion;

	// Convert from degrees to radians:
	angle *= Constants::DEGREES_TO_RADIANS;
	float halfAngle = angle * 0.5f;

	quartenion.w = cosf(halfAngle);

	// Normalize axis:
	Vector3<float> normalizedAxis = axis.normalizedVector();
	
	float sinHalfAngle = sinf(halfAngle);
	quartenion.x = normalizedAxis.x * sinHalfAngle;
	quartenion.y = normalizedAxis.y * sinHalfAngle;
	quartenion.z = normalizedAxis.z * sinHalfAngle;

	return quartenion;
}

Quartenion Quartenion::FromEulerAngles(float roll, float pitch, float yaw)
{
	/*Quartenion rollQuartenion = FromAxisAngle(Vector3<float>(1.0f, 0.0f, 0.0f), roll);
	Quartenion pitchQuartenion = FromAxisAngle(Vector3<float>(0.0f, 1.0f, 0.0f), pitch);
	Quartenion yawQuartenion = FromAxisAngle(Vector3<float>(0.0f, 0.0f, 1.0f), yaw);

	return yawQuartenion * pitchQuartenion * rollQuartenion;*/
	return Quartenion();
}

Vector3<float> operator*(const Quartenion& quartenion, const Vector3<float>& vector)
{
}