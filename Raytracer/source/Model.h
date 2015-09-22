#pragma once

#include <glm\matrix.hpp>

#include "Material.h"
#include "Ray.h"

template<class MeshType>
class Model
{
public:
	Model();
	Model(const MeshType& mesh, const Material& material);

	void Initialize(const MeshType& mesh, const Material& material);

	bool Intersect(const Ray& ray, Point<>& intersection, float& distance, Vector3<>& normal) const;

	const Material& GetMaterial() const;
	const glm::mat4& GetTransform() const;

private:
	MeshType m_mesh;
	Material m_material;
};

template<class MeshType>
inline Model<MeshType>::Model()
{
}

template<class MeshType>
inline Model<MeshType>::Model(const MeshType & mesh, const Material & material) :
	m_mesh(mesh),
	m_material(material)
{
}

template<class MeshType>
inline void Model<MeshType>::Initialize(const MeshType& mesh, const Material& material)
{
	m_mesh = mesh;
	m_material = material;
}

template<class MeshType>
inline bool Model<MeshType>::Intersect(const Ray & ray, Point<>& intersection, float& distance, Vector3<>& normal) const
{
	return static_cast<MeshType>(m_mesh).Intersect(ray, intersection, distance, normal);
}

template<class MeshType>
inline const Material& Model<MeshType>::GetMaterial() const
{
	return m_material;
}

template<class MeshType>
inline const glm::mat4 & Model<MeshType>::GetTransform() const
{
	return m_transform;
}
