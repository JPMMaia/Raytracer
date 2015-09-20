#pragma once

template<class T>
class PoolObject
{
public:
	PoolObject()
	{
		m_active = false;
	}

	void Activate()
	{
		// Set to active state:
		m_active = true;
	}
	void Deactivate()
	{
		// Set to inactive state:
		m_active = false;
	}

	PoolObject<T>* GetNext() const
	{
		return m_next;
	}
	void SetNext(PoolObject<T>* next)
	{
		m_next = next;
	}
	T* GetObjectPointer()
	{
		return &m_object;
	}
	bool IsActive() const
	{
		return m_active;
	}

private:
	PoolObject<T>* m_next;
	T m_object;
	bool m_active;
};