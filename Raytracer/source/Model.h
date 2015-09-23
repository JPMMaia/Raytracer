#pragma once

#include <glm\matrix.hpp>

#include "Material.h"
#include "Ray.h"

template<class MeshType>
class Model
{
public:
	Model();
	Model(const MeshType& mesh, const Material& material, const glm::mat4& transform);

	void Initialize(const MeshType& mesh, const Material& material, const glm::mat4& transform);

	bool Intersect(const Ray& ray, Point<>& intersection, float& distance, Vector3<>& normal) const;

	const Material& GetMaterial() const;
	const glm::mat4& GetTransform() const;
	const glm::mat4& GetInverseTransform() const;

private:
	MeshType m_mesh;
	Material m_material;
	glm::mat4 m_transform;
	glm::mat4 m_inverseTransform;
};

template<class MeshType>
inline Model<MeshType>::Model()
{
}

template<class MeshType>
inline Model<MeshType>::Model(const MeshType & mesh, const Material & material, const glm::mat4& transform)
{
	Initialize(mesh, material, transform);
}

template<class MeshType>
inline void Model<MeshType>::Initialize(const MeshType& mesh, const Material& material, const glm::mat4& transform)
{
	m_mesh = mesh;
	m_material = material;
	m_transform = transform;
	m_inverseTransform = glm::inverse(transform);
}

template<class MeshType>
inline bool Model<MeshType>::Intersect(const Ray& ray, Point<>& intersection, float& distance, Vector3<>& normal) const
{
	//Ray transformedRay(ray);
	Ray transformedRay;
	transformedRay.origin = m_inverseTransform * ray.origin;
	transformedRay.direction = m_inverseTransform * ray.direction;
	transformedRay.direction.normalize();

	if (!static_cast<MeshType>(m_mesh).Intersect(transformedRay, intersection, distance, normal))
		return false;

	intersection = m_transform * intersection;
	normal = m_transform * normal;
	normal.normalize();
	
	return true;
}

template<class MeshType>
inline const Material& Model<MeshType>::GetMaterial() const
{
	return m_material;
}

template<class MeshType>
inline const glm::mat4& Model<MeshType>::GetTransform() const
{
	return m_transform;
}

template<class MeshType>
inline const glm::mat4 & Model<MeshType>::GetInverseTransform() const
{
	return m_inverseTransform;
}
