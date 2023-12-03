#ifndef TYPE_H
#define TYPE_H
#include "multidimensiondata.h"
#include "Eigen/Core"
#include "Eigen/Dense"

typedef Eigen::Matrix4f Mat4f;
typedef Eigen::Matrix3f Mat3f;
typedef Eigen::Vector4f Vec4f;
typedef Eigen::Vector3f Vec3f;
typedef Eigen::Vector2f Vec2f;

typedef MultiDimensionData<float,3> VertexCoordinates;
typedef MultiDimensionData<float,2> TextureCoordinates;
typedef MultiDimensionData<unsigned int,3> TriangleIndices;

#endif // TYPE_H
