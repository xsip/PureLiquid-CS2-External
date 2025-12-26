#pragma once
#include <Math/Definitions.h>
#include <Math/Vector.h>
struct Matrix3x4_t;
struct MATH_API Quaternion_t
{
	constexpr Quaternion_t(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f, const float w = 0.0f);

	[[nodiscard]] bool IsValid() const;

	/// @param[in] vecOrigin [optional] translation for converted matrix
	/// @returns: matrix converted from quaternion
	[[nodiscard]] Matrix3x4_t ToMatrix(const Vector& vecOrigin = {}) const;

	float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;
};

struct alignas(16) MATH_API QuaternionAligned_t : Quaternion_t
{
	QuaternionAligned_t& operator=(const Quaternion_t& quatOther);
};

static_assert(alignof(QuaternionAligned_t) == 16);

using Quaternion = Quaternion_t;