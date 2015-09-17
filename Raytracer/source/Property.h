#pragma once

template<class T>
struct Property
{
public:
	inline Property& operator=(const T& value)
	{
		m_value = value;

		return *this;
	}

private:
	T m_value;
};