#include <Math/Ray.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Math/QAngle.h>
#include <algorithm>
#include <cmath>
#include <cfloat>
#include <vector>

void OBB::FromMatrixAndAABB(const Matrix2x4_t& m, const Vector& aabbMin, const Vector& aabbMax)
{
    Vector3 center = (aabbMin + aabbMax) * 0.5f;
    Vector3 half = (aabbMax - aabbMin) * 0.5f;

    origin = m.GetOrigin(); /* bone world Z offset here, probably aabbMin.z or aabbMax.z */;

    // Axes
    axes[0] = Vector3(m._11, m._12, m._13);
    axes[1] = Vector3(m._21, m._22, m._23);
    axes[2] = axes[0].CrossProduct(axes[1]);

    axes[0] = axes[0].Normalized();
    axes[1] = axes[1].Normalized();
    axes[2] = axes[2].Normalized();

    halfSize = half;
}

OBB OBB::BuildHullFromAllBones(const std::vector<Matrix2x4_t>& boneMatrices)
{
    if (boneMatrices.empty() )
        return OBB{}; // empty hull

    // Initialize min/max to first bone
    Vector3 firstPos = boneMatrices[6].GetOrigin();
    Vector3 vMin = firstPos;
    Vector3 vMax = firstPos;

    // Expand min/max based on all selected bones
    for (int bone = 0; bone < 104; bone ++)
    {
        const Vector3 pos = boneMatrices[bone].GetOrigin();
        vMin.x = std::min(vMin.x, pos.x);
        vMin.y = std::min(vMin.y, pos.y);
        vMin.z = std::min(vMin.z, pos.z);

        vMax.x = std::max(vMax.x, pos.x);
        vMax.y = std::max(vMax.y, pos.y);
        vMax.z = std::max(vMax.z, pos.z);
    }

    OBB hull;
    hull.origin = (vMin + vMax) * 0.5f;
    hull.halfSize = (vMax - vMin) * 0.5f;

    // Optional: orient axes along the longest span
    Vector3 span = vMax - vMin;
    if (span.LengthSqr() > 0.0f)
    {
        Vector3 forward = span.Normalized();
        Vector3 tmp = (fabs(forward.x) < 0.99f) ? Vector3(1, 0, 0) : Vector3(0, 1, 0);
        Vector3 right = forward.CrossProduct(tmp).Normalized();
        Vector3 up = forward.CrossProduct(right).Normalized();

        hull.axes[0] = forward;
        hull.axes[1] = right;
        hull.axes[2] = up;
    }
    else
    {
        hull.axes[0] = Vector3(1, 0, 0);
        hull.axes[1] = Vector3(0, 1, 0);
        hull.axes[2] = Vector3(0, 0, 1);
    }

    return hull;
}

OBB OBB::BuildHullFromBones(const std::vector<Matrix2x4_t>& boneMatrices, const std::vector<int>& bonesToInclude)
{
    if (boneMatrices.empty() || bonesToInclude.empty())
        return OBB{}; // empty hull

    // Initialize min/max to first bone
    Vector3 firstPos = boneMatrices[bonesToInclude[0]].GetOrigin();
    Vector3 vMin = firstPos;
    Vector3 vMax = firstPos;

    // Expand min/max based on all selected bones
    for (int bone : bonesToInclude)
    {
        const Vector3 pos = boneMatrices[bone].GetOrigin();
        vMin.x = std::min(vMin.x, pos.x);
        vMin.y = std::min(vMin.y, pos.y);
        vMin.z = std::min(vMin.z, pos.z);

        vMax.x = std::max(vMax.x, pos.x);
        vMax.y = std::max(vMax.y, pos.y);
        vMax.z = std::max(vMax.z, pos.z);
    }

    OBB hull;
    hull.origin = (vMin + vMax) * 0.5f;
    hull.halfSize = (vMax - vMin) * 0.5f;

    // Optional: orient axes along the longest span
    Vector3 span = vMax - vMin;
    if (span.LengthSqr() > 0.0f)
    {
        Vector3 forward = span.Normalized();
        Vector3 tmp = (fabs(forward.x) < 0.99f) ? Vector3(1, 0, 0) : Vector3(0, 1, 0);
        Vector3 right = forward.CrossProduct(tmp).Normalized();
        Vector3 up = forward.CrossProduct(right).Normalized();

        hull.axes[0] = forward;
        hull.axes[1] = right;
        hull.axes[2] = up;
    }
    else
    {
        hull.axes[0] = Vector3(1, 0, 0);
        hull.axes[1] = Vector3(0, 1, 0);
        hull.axes[2] = Vector3(0, 0, 1);
    }

    return hull;
}

Ray::Ray(const Vector3& origin, const Vector3& direction)
    : m_origin(origin), m_direction(direction) {
    m_direction = m_direction.Normalized();
}

inline float fast_abs(float f) {
    int i = *reinterpret_cast<int*>(&f);
    i &= 0x7FFFFFFF;
    return *reinterpret_cast<float*>(&i);
}


bool Ray::IntersectWithOBB(const OBB& obb, float& outDistance) const
{
    Vector3 delta = obb.origin - m_origin;
    float tMin = -FLT_MAX;
    float tMax = FLT_MAX;

    for (int i = 0; i < 3; ++i)
    {
        float axisDotDir = m_direction.DotProduct(obb.axes[i]);
        float axisDotDelta = delta.DotProduct(obb.axes[i]);
        float h = obb.halfSize[i];

        if (fabs(axisDotDir) < 1e-6f) // ray parallel to slab
        {
            if (axisDotDelta < -h || axisDotDelta > h)
                return false;
        }
        else
        {
            float t1 = (axisDotDelta - h) / axisDotDir;
            float t2 = (axisDotDelta + h) / axisDotDir;
            if (t1 > t2) std::swap(t1, t2);

            if (t1 > tMin) tMin = t1;
            if (t2 < tMax) tMax = t2;

            if (tMin > tMax)
                return false;
        }
    }

    outDistance = (tMin >= 0.0f) ? tMin : tMax;
    return outDistance >= 0.0f;
}
/*bool Ray::IntersectWithOBB(const OBB& obb, float& outDistance) const {
    Vector3 delta = obb.origin - m_origin;
    float tMin = -FLT_MAX, tMax = FLT_MAX;

    // X-axis
    float d = m_direction.DotProductSIMD(obb.axes[0]);
    float e = delta.DotProductSIMD(obb.axes[0]);
    if (fast_abs(d) < 1e-6f) {
        if (e < -obb.halfSize.x || e > obb.halfSize.x) return false;
    }
    else {
        float t1 = (e - obb.halfSize.x) / d;
        float t2 = (e + obb.halfSize.x) / d;
        if (t1 > t2) { float tmp = t1; t1 = t2; t2 = tmp; }

        tMin = (t1 > tMin) ? t1 : tMin;
        tMax = (t2 < tMax) ? t2 : tMax;

        if (tMin > tMax) return false;
    }

    // Y-axis
    d = m_direction.DotProductSIMD(obb.axes[1]);
    e = delta.DotProductSIMD(obb.axes[1]);
    if (fast_abs(d) < 1e-6f) {
        if (e < -obb.halfSize.y || e > obb.halfSize.y) return false;
    }
    else {
        float t1 = (e - obb.halfSize.y) / d;
        float t2 = (e + obb.halfSize.y) / d;
        if (t1 > t2) { float tmp = t1; t1 = t2; t2 = tmp; }

        tMin = (t1 > tMin) ? t1 : tMin;
        tMax = (t2 < tMax) ? t2 : tMax;

        if (tMin > tMax) return false;
    }

    // Z-axis
    d = m_direction.DotProductSIMD(obb.axes[2]);
    e = delta.DotProductSIMD(obb.axes[2]);
    if (fast_abs(d) < 1e-6f) {
        if (e < -obb.halfSize.z || e > obb.halfSize.z) return false;
    }
    else {
        float t1 = (e - obb.halfSize.z) / d;
        float t2 = (e + obb.halfSize.z) / d;
        if (t1 > t2) { float tmp = t1; t1 = t2; t2 = tmp; }

        tMin = (t1 > tMin) ? t1 : tMin;
        tMax = (t2 < tMax) ? t2 : tMax;

        if (tMin > tMax) return false;
    }

    outDistance = (tMin >= 0.0f) ? tMin : tMax;
    return true;
}*/