#pragma once

#include "Material.h"
#include "Ray.h"

template<class MeshType>
class Model
{
public:
	Model();
	Model(const MeshType& mesh, const Material& material);

	bool Intersect(const Ray& ray, Point<>& intersection, Vector<>& normal) const;

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
inline bool Model<MeshType>::Intersect(const Ray & ray, Point<>& intersection, Vector<>& normal) const
{
	return static_cast<MeshType>(m_mesh).Intersect(ray, intersection, normal);
}
