#pragma once
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <vector>

struct MATH_API OBB
{
    Vector3 origin;
    Vector3 axes[3];
    Vector3 halfSize;

    void FromMatrixAndAABB(const Matrix2x4_t& m, const Vector& aabbMin, const Vector& aabbMax);

    static OBB BuildHullFromBones(const std::vector<Matrix2x4_t>& boneMatrices, const std::vector<int>& bonesToInclude);
    static OBB BuildHullFromAllBones(const std::vector<Matrix2x4_t>& boneMatrices);
};

class MATH_API Ray {
public:
    Ray(const Vector3& origin, const Vector3& direction);

    bool IntersectWithOBB(const OBB& obb, float &) const;

public:
    Vector3 m_origin;
    Vector3 m_direction;
};