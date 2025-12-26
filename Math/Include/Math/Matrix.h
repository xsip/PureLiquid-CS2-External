#pragma once
// used: sse2 intrinsics
#include <xmmintrin.h>
// used: bit_cast
#include <bit>
#include <vector>
#include <Math/Definitions.h>
#include <Math/Vector.h>
// forward declarations
struct QAngle_t;

// #pragma pack(push, 4)
using Matrix3x3_t = float[3][3];


struct MATH_API view_matrix_t {
	float* operator[ ](int index);
	float matrix[4][4]{};
};


struct MATH_API Matrix3x4_t
{
	Matrix3x4_t() = default;

	Matrix3x4_t(
		const float m00, const float m01, const float m02, const float m03,
		const float m10, const float m11, const float m12, const float m13,
		const float m20, const float m21, const float m22, const float m23);

	Matrix3x4_t(const Vector& vecForward, const Vector& vecLeft, const Vector& vecUp, const Vector& vecOrigin);

	[[nodiscard]] float* operator[](const int nIndex);

	[[nodiscard]] const float* operator[](const int nIndex) const;
	

	void SetForward(const Vector& vecForward);

	void SetLeft(const Vector& vecLeft);

	void SetUp(const Vector& vecUp);

	void SetOrigin(const Vector& vecOrigin);

	[[nodiscard]] Vector GetForward() const;

	[[nodiscard]] Vector GetLeft() const;

	[[nodiscard]] Vector GetUp() const;

	[[nodiscard]] Vector GetOrigin() const;

	void Invalidate();

	/// concatenate transformations of two matrices into one
	/// @returns: matrix with concatenated transformations
	[[nodiscard]] Matrix3x4_t ConcatTransforms(const Matrix3x4_t& matOther) const;

	Vector TransformVector(const Vector& v) const;
	Vector TransformPoint(const Vector& v) const;


	[[nodiscard]] const Vector GetOrigin(int nIndex);

	/// @returns: angles converted from this matrix
	[[nodiscard]] QAngle_t ToAngles() const;

	float arrData[3][4]{};
};

// #pragma pack(pop)

class alignas(16) MATH_API Matrix3x4a_t : public Matrix3x4_t
{
public:
	Matrix3x4a_t() = default;

	Matrix3x4a_t(
		const float m00, const float m01, const float m02, const float m03,
		const float m10, const float m11, const float m12, const float m13,
		const float m20, const float m21, const float m22, const float m23);

	Matrix3x4a_t(const Matrix3x4_t& matSource);

	Matrix3x4a_t& operator=(const Matrix3x4_t& matSource);

	/// concatenate transformations of two aligned matrices into one
	/// @returns: aligned matrix with concatenated transformations
	[[nodiscard]] Matrix3x4a_t ConcatTransforms(const Matrix3x4a_t& matOther) const;
};

static_assert(alignof(Matrix3x4a_t) == 16);

// #pragma pack(push, 4)

struct MATH_API ViewMatrix_t
{
	ViewMatrix_t() = default;

	ViewMatrix_t(
		const float m00, const float m01, const float m02, const float m03,
		const float m10, const float m11, const float m12, const float m13,
		const float m20, const float m21, const float m22, const float m23,
		const float m30, const float m31, const float m32, const float m33);
	ViewMatrix_t(const Matrix3x4_t& matFrom, const Vector4D_t& vecAdditionalRow = {});

	[[nodiscard]] float* operator[](const int nIndex);
	[[nodiscard]] const float* operator[](const int nIndex) const;

	[[nodiscard]] const bool operator==(const ViewMatrix_t& viewOther) const;

	[[nodiscard]] const Matrix3x4_t& As3x4() const;

	[[nodiscard]] Matrix3x4_t& As3x4();

	ViewMatrix_t& operator+=(const ViewMatrix_t& matAdd);

	ViewMatrix_t& operator-=(const ViewMatrix_t& matSubtract);
	[[nodiscard]] Vector4D_t GetRow(const int nIndex) const;

	[[nodiscard]] Vector4D_t GetColumn(const int nIndex) const;

	void Identity();

	/// concatenate transformations of two matrices into one
	/// @returns: matrix with concatenated transformations
	[[nodiscard]] ViewMatrix_t ConcatTransforms(const ViewMatrix_t& matOther) const;

	float arrData[4][4]{};
};

// #pragma pack(pop)

struct MATH_API Matrix2x4_t
{
private:
public:
	Matrix2x4_t(Matrix2x4_t* m);
	Matrix2x4_t();
	~Matrix2x4_t();
	Matrix3x4_t TranslateToMatrix3x4();

	[[nodiscard]] Vector GetOrigin() const;
	[[nodiscard]] Vector GetOrigin(int nIndex) const;

	Vector TransformPosition(const Vector& local) const;

	void SetOrigin(int nIndex, Vector vecValue);

	[[nodiscard]] Vector4D_t GetRotation() const;
	[[nodiscard]] Vector4D_t GetRotation(int nIndex) const;



	float _11 = 0.0f, _12 = 0.0f, _13 = 0.0f, _14 = 0.0f;
	float _21 = 0.0f, _22 = 0.0f, _23 = 0.0f, _24 = 0.0f;

};
