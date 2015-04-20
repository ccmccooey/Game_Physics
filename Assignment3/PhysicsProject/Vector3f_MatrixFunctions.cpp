#include "Vector3f.h"
#include "Matrix44f.h"

Vector3f Vector3f::LocalToWorld(const Vector3f &local, const Matrix44f* transform)
{
	return transform->TransformInverse(local);
}
Vector3f Vector3f::WorldToWorld(const Vector3f &world, const Matrix44f* transform)
{
	return transform->TransformInverse(world);
}