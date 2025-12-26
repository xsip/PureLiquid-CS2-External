#pragma once
// used: [stl] numeric_limits
#include <limits>
// used: [crt] isfinite, fmodf, sqrtf
#include <cmath>
#include <Math/Definitions.h>
#include <Math/Core.h>
// forward declarations
struct QAngle_t;
struct Matrix3x4_t;
struct ViewMatrix_t;
struct view_matrix_t;
// @source: master/public/mathlib/vector.h

struct MATH_API Vector2D_t
{
	constexpr Vector2D_t(const float x = 0.0f, const float y = 0.0f);

	[[nodiscard]] bool IsZero() const;

	float x = 0.0f, y = 0.0f;
};

struct MATH_API Vector
{

	constexpr Vector(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f);

	constexpr Vector(const float* arrVector);

	constexpr Vector(const Vector2D_t& vecBase2D);

	void AngleVectors(Vector* forward, Vector* right, Vector* up);

#pragma region vector_array_operators

	[[nodiscard]] float& operator[](const int nIndex);

	[[nodiscard]] const float& operator[](const int nIndex) const;

#pragma endregion

#pragma region vector_relational_operators

	bool operator==(const Vector& vecBase) const;
	bool operator!=(const Vector& vecBase) const;
#pragma endregion

#pragma region vector_assignment_operators
	constexpr Vector& operator=(const Vector& vecBase);
	constexpr Vector& operator=(const Vector2D_t& vecBase2D);

#pragma endregion

#pragma region vector_arithmetic_assignment_operators

	constexpr Vector& operator+=(const Vector& vecBase);

	constexpr Vector& operator-=(const Vector& vecBase);
	constexpr Vector& operator*=(const Vector& vecBase);
	constexpr Vector& operator/=(const Vector& vecBase);

	constexpr Vector& operator+=(const float flAdd);

	constexpr Vector& operator-=(const float flSubtract);

	constexpr Vector& operator*=(const float flMultiply);

	constexpr Vector& operator/=(const float flDivide);

#pragma endregion

#pragma region vector_arithmetic_unary_operators

	constexpr Vector& operator-();

	constexpr Vector operator-() const;

#pragma endregion

#pragma region vector_arithmetic_ternary_operators

	Vector operator+(const Vector& vecAdd) const;
	Vector operator-(const Vector& vecSubtract) const;

	Vector operator*(const Vector& vecMultiply) const;

	Vector operator/(const Vector& vecDivide) const;

	Vector operator+(const float flAdd) const;

	Vector operator-(const float flSubtract) const;

	Vector operator*(const float flMultiply) const;

	Vector operator/(const float flDivide) const;
#pragma endregion

	/// @returns: true if each component of the vector is finite, false otherwise
	[[nodiscard]] bool IsValid() const;

	constexpr void Invalidate();

	/// @returns: true if each component of the vector equals to another, false otherwise
	[[nodiscard]] bool IsEqual(const Vector& vecEqual, const float flErrorMargin = std::numeric_limits<float>::epsilon()) const;

	/// @returns: true if each component of the vector equals to zero, false otherwise
	[[nodiscard]] bool IsZero() const;

	[[nodiscard]] float Length() const;

	[[nodiscard]] constexpr float LengthSqr() const;
	[[nodiscard]] float Length2D() const;

	[[nodiscard]] constexpr float Length2DSqr() const;

	[[nodiscard]] float DistTo(const Vector& vecEnd) const;

	[[nodiscard]] constexpr float DistToSqr(const Vector& vecEnd) const;

	/// normalize magnitude of each component of the vector
	/// @returns: length of the vector
	float NormalizeInPlace();

	/// normalize magnitude of each component of the vector
	/// @returns: copy of the vector with normalized components
	[[nodiscard]] Vector Normalized() const;

	[[nodiscard]] constexpr float DotProduct(const Vector& vecDot) const;

	[[nodiscard]] float DotProductSIMD(const Vector& b) const;

	[[nodiscard]] constexpr Vector CrossProduct(const Vector& vecCross) const;

	/// @returns: transformed vector by given transformation matrix
	[[nodiscard]] Vector Transform(const Matrix3x4_t& matTransform) const;

	[[nodiscard]] Vector2D_t ToVector2D() const;

	/// convert forward direction vector to other direction vectors
	/// @param[out] pvecRight [optional] output for converted right vector
	/// @param[out] pvecUp [optional] output for converted up vector
	void ToDirections(Vector* pvecRight, Vector* pvecUp) const;

	/// @returns: 2D angles converted from direction vector
	[[nodiscard]] QAngle_t ToAngles() const;
	[[nodiscard]] QAngle_t RelativeAngle() const;
	[[nodiscard]] bool ToScreen(ViewMatrix_t, int, int, Vector&) const;
	[[nodiscard]] bool ToScreenSSE(const ViewMatrix_t& vm, int screenWidth, int screenHeight, Vector& out) const;
	[[nodiscard]] bool ToScreenDota(ViewMatrix_t, int, int, Vector&) const;

	/// @returns: matrix converted from forward direction vector
	[[nodiscard]] Matrix3x4_t ToMatrix() const;


	Vector ComponentMin(const Vector& other) const;

	// Returns a new vector with the max of each component
	Vector ComponentMax(const Vector& other) const;

	float x = 0.0f, y = 0.0f, z = 0.0f;
};

struct MATH_API Vector4D_t
{
	constexpr Vector4D_t(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f, const float w = 0.0f) :
		x(x), y(y), z(z), w(w) {
	}
	Vector ToVector();
	float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;
};

struct alignas(16) MATH_API VectorAligned_t : Vector
{
	VectorAligned_t() = default;

	explicit VectorAligned_t(const Vector& vecBase);

	constexpr VectorAligned_t& operator=(const Vector& vecBase);

	float w = 0.0f;
};

static_assert(alignof(VectorAligned_t) == 16);

using Vector3 = Vector;