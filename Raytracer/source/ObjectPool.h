#pragma once

#include <vector>
#include <exception>

#include "PoolObject.h"

typedef unsigned int UINT;

template<class T>
class ObjectPool
{
public:
	void Initialize(UINT size);
	bool Create(T*& object);

private:
	std::vector<PoolObject<T>> m_pool;
	PoolObject<T>* m_firstAvailable;
};

template<class T>
inline void ObjectPool<T>::Initialize(UINT size)
{	
#if _DEBUG
	if (size == 0)
		throw std::exception("ObjectPool::Initialize: Size was 0.");
#endif

	// Resize vector:
	m_pool.resize(size);

	// The first in the pool is the first available:
	m_firstAvailable = &m_pool[0];

	// Build the "union" linked list:
	for (UINT i = 0; i < m_pool.size() - 1; i++)
		m_pool[i].SetNext(&m_pool[i + 1]);

	// The last one ends the list:
	m_pool[m_pool.size() - 1].SetNext(nullptr);
}

template<class T>
inline bool ObjectPool<T>::Create(T*& object)
{
	// If the pool is full:
	if (!m_firstAvailable)
		return false;

	// Remove first available pool object from the linked list:
	PoolObject<T>* poolObject = m_firstAvailable;
	m_firstAvailable = poolObject->GetNext();

	poolObject->Activate();

	// Return object pointer so that it can be initialized:
	object = poolObject->GetObjectPointer();

	return true;
}