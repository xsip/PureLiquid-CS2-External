#include <Math/Matrix.h>
#include <Math/Core.h>
#include <Math/Vector.h>
#include <Math/QAngle.h>


float* view_matrix_t::operator[ ](int index) {
	return matrix[index];
}



Matrix3x4_t::Matrix3x4_t(
	const float m00, const float m01, const float m02, const float m03,
	const float m10, const float m11, const float m12, const float m13,
	const float m20, const float m21, const float m22, const float m23)
{
	arrData[0][0] = m00;
	arrData[0][1] = m01;
	arrData[0][2] = m02;
	arrData[0][3] = m03;
	arrData[1][0] = m10;
	arrData[1][1] = m11;
	arrData[1][2] = m12;
	arrData[1][3] = m13;
	arrData[2][0] = m20;
	arrData[2][1] = m21;
	arrData[2][2] = m22;
	arrData[2][3] = m23;
}

Matrix3x4_t::Matrix3x4_t(const Vector& vecForward, const Vector& vecLeft, const Vector& vecUp, const Vector& vecOrigin)
{
	SetForward(vecForward);
	SetLeft(vecLeft);
	SetUp(vecUp);
	SetOrigin(vecOrigin);
}

[[nodiscard]] float* Matrix3x4_t::operator[](const int nIndex)
{
	return arrData[nIndex];
}

[[nodiscard]] const float* Matrix3x4_t::operator[](const int nIndex) const
{
	return arrData[nIndex];
}

void Matrix3x4_t::SetForward(const Vector& vecForward)
{
	arrData[0][0] = vecForward.x;
	arrData[1][0] = vecForward.y;
	arrData[2][0] = vecForward.z;
}

void Matrix3x4_t::SetLeft(const Vector& vecLeft)
{
	arrData[0][1] = vecLeft.x;
	arrData[1][1] = vecLeft.y;
	arrData[2][1] = vecLeft.z;
}

void Matrix3x4_t::SetUp(const Vector& vecUp)
{
	arrData[0][2] = vecUp.x;
	arrData[1][2] = vecUp.y;
	arrData[2][2] = vecUp.z;
}

void Matrix3x4_t::SetOrigin(const Vector& vecOrigin)
{
	arrData[0][3] = vecOrigin.x;
	arrData[1][3] = vecOrigin.y;
	arrData[2][3] = vecOrigin.z;
}

[[nodiscard]] Vector Matrix3x4_t::GetForward() const
{
	return { arrData[0][0], arrData[1][0], arrData[2][0] };
}

[[nodiscard]] Vector Matrix3x4_t::GetLeft() const
{
	return { arrData[0][1], arrData[1][1], arrData[2][1] };
}

[[nodiscard]] Vector Matrix3x4_t::GetUp() const
{
	return { arrData[0][2], arrData[1][2], arrData[2][2] };
}

[[nodiscard]] Vector Matrix3x4_t::GetOrigin() const
{
	return { arrData[0][3], arrData[1][3], arrData[2][3] };
}

void Matrix3x4_t::Invalidate()
{
	for (auto& arrSubData : arrData)
	{
		for (auto& flData : arrSubData)
			flData = std::numeric_limits<float>::infinity();
	}
}

/// concatenate transformations of two matrices into one
/// @returns: matrix with concatenated transformations
[[nodiscard]] Matrix3x4_t Matrix3x4_t::ConcatTransforms(const Matrix3x4_t& matOther) const
{
	return {
		arrData[0][0] * matOther.arrData[0][0] + arrData[0][1] * matOther.arrData[1][0] + arrData[0][2] * matOther.arrData[2][0],
		arrData[0][0] * matOther.arrData[0][1] + arrData[0][1] * matOther.arrData[1][1] + arrData[0][2] * matOther.arrData[2][1],
		arrData[0][0] * matOther.arrData[0][2] + arrData[0][1] * matOther.arrData[1][2] + arrData[0][2] * matOther.arrData[2][2],
		arrData[0][0] * matOther.arrData[0][3] + arrData[0][1] * matOther.arrData[1][3] + arrData[0][2] * matOther.arrData[2][3] + arrData[0][3],

		arrData[1][0] * matOther.arrData[0][0] + arrData[1][1] * matOther.arrData[1][0] + arrData[1][2] * matOther.arrData[2][0],
		arrData[1][0] * matOther.arrData[0][1] + arrData[1][1] * matOther.arrData[1][1] + arrData[1][2] * matOther.arrData[2][1],
		arrData[1][0] * matOther.arrData[0][2] + arrData[1][1] * matOther.arrData[1][2] + arrData[1][2] * matOther.arrData[2][2],
		arrData[1][0] * matOther.arrData[0][3] + arrData[1][1] * matOther.arrData[1][3] + arrData[1][2] * matOther.arrData[2][3] + arrData[1][3],

		arrData[2][0] * matOther.arrData[0][0] + arrData[2][1] * matOther.arrData[1][0] + arrData[2][2] * matOther.arrData[2][0],
		arrData[2][0] * matOther.arrData[0][1] + arrData[2][1] * matOther.arrData[1][1] + arrData[2][2] * matOther.arrData[2][1],
		arrData[2][0] * matOther.arrData[0][2] + arrData[2][1] * matOther.arrData[1][2] + arrData[2][2] * matOther.arrData[2][2],
		arrData[2][0] * matOther.arrData[0][3] + arrData[2][1] * matOther.arrData[1][3] + arrData[2][2] * matOther.arrData[2][3] + arrData[2][3]
	};
}

Vector Matrix3x4_t::TransformVector(const Vector& v) const
{
	return {
		v.x * arrData[0][0] + v.y * arrData[0][1] + v.z * arrData[0][2] + arrData[0][3],
		v.x * arrData[1][0] + v.y * arrData[1][1] + v.z * arrData[1][2] + arrData[1][3],
		v.x * arrData[2][0] + v.y * arrData[2][1] + v.z * arrData[2][2] + arrData[2][3]
	};
}

Vector Matrix3x4_t::TransformPoint(const Vector& v) const
{
	return Vector(
		v.x * arrData[0][0] + v.y * arrData[0][1] + v.z * arrData[0][2] + arrData[0][3],
		v.x * arrData[1][0] + v.y * arrData[1][1] + v.z * arrData[1][2] + arrData[1][3],
		v.x * arrData[2][0] + v.y * arrData[2][1] + v.z * arrData[2][2] + arrData[2][3]
	);
}

[[nodiscard]] const Vector Matrix3x4_t::GetOrigin(int nIndex)
{
	return { this[nIndex].arrData[0][3], this[nIndex].arrData[1][3], this[nIndex].arrData[2][3] };
}

[[nodiscard]] QAngle_t Matrix3x4_t::ToAngles() const
{
	// extract the basis vectors from the matrix. since we only need the z component of the up vector, we don't get x and y
	const Vector vecForward = this->GetForward();
	const Vector vecLeft = this->GetLeft();
	const float flUpZ = this->arrData[2][2];

	const float flLength2D = vecForward.Length2D();
	const float flPitch = M_RAD2DEG(std::atan2f(-vecForward.z, flLength2D));

	// check is enough here to get angles
	if (flLength2D > 0.001f)
		return { flPitch, M_RAD2DEG(std::atan2f(vecForward.y, vecForward.x)), M_RAD2DEG(std::atan2f(vecLeft.z, flUpZ)) };

	// forward is mostly Z, gimbal lock
	// assume no roll in this case as one degree of freedom has been lost (i.e. yaw equals roll)
	return { flPitch, M_RAD2DEG(std::atan2f(-vecLeft.x, vecLeft.y)), 0.0f };
}





Matrix3x4a_t::Matrix3x4a_t(
	const float m00, const float m01, const float m02, const float m03,
	const float m10, const float m11, const float m12, const float m13,
	const float m20, const float m21, const float m22, const float m23)
{
	arrData[0][0] = m00;
	arrData[0][1] = m01;
	arrData[0][2] = m02;
	arrData[0][3] = m03;
	arrData[1][0] = m10;
	arrData[1][1] = m11;
	arrData[1][2] = m12;
	arrData[1][3] = m13;
	arrData[2][0] = m20;
	arrData[2][1] = m21;
	arrData[2][2] = m22;
	arrData[2][3] = m23;
}

Matrix3x4a_t::Matrix3x4a_t(const Matrix3x4_t& matSource)
{
	*this = matSource;
}

Matrix3x4a_t& Matrix3x4a_t::operator=(const Matrix3x4_t& matSource)
{
	arrData[0][0] = matSource.arrData[0][0];
	arrData[0][1] = matSource.arrData[0][1];
	arrData[0][2] = matSource.arrData[0][2];
	arrData[0][3] = matSource.arrData[0][3];
	arrData[1][0] = matSource.arrData[1][0];
	arrData[1][1] = matSource.arrData[1][1];
	arrData[1][2] = matSource.arrData[1][2];
	arrData[1][3] = matSource.arrData[1][3];
	arrData[2][0] = matSource.arrData[2][0];
	arrData[2][1] = matSource.arrData[2][1];
	arrData[2][2] = matSource.arrData[2][2];
	arrData[2][3] = matSource.arrData[2][3];
	return *this;
}

/// concatenate transformations of two aligned matrices into one
/// @returns: aligned matrix with concatenated transformations
[[nodiscard]] Matrix3x4a_t Matrix3x4a_t::ConcatTransforms(const Matrix3x4a_t& matOther) const
{
	Matrix3x4a_t matOutput;
	// CS_ASSERT((reinterpret_cast<std::uintptr_t>(this) & 15U) == 0 && (reinterpret_cast<std::uintptr_t>(&matOther) & 15U) == 0 && (reinterpret_cast<std::uintptr_t>(&matOutput) & 15U) == 0); // matrices aren't aligned

	__m128 thisRow0 = _mm_load_ps(this->arrData[0]);
	__m128 thisRow1 = _mm_load_ps(this->arrData[1]);
	__m128 thisRow2 = _mm_load_ps(this->arrData[2]);

	__m128 otherRow0 = _mm_load_ps(matOther.arrData[0]);
	__m128 otherRow1 = _mm_load_ps(matOther.arrData[1]);
	__m128 otherRow2 = _mm_load_ps(matOther.arrData[2]);

	__m128 outRow0 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(thisRow0, thisRow0, _MM_SHUFFLE(0, 0, 0, 0)), otherRow0), _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(thisRow0, thisRow0, _MM_SHUFFLE(1, 1, 1, 1)), otherRow1), _mm_mul_ps(_mm_shuffle_ps(thisRow0, thisRow0, _MM_SHUFFLE(2, 2, 2, 2)), otherRow2)));
	__m128 outRow1 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(thisRow1, thisRow1, _MM_SHUFFLE(0, 0, 0, 0)), otherRow0), _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(thisRow1, thisRow1, _MM_SHUFFLE(1, 1, 1, 1)), otherRow1), _mm_mul_ps(_mm_shuffle_ps(thisRow1, thisRow1, _MM_SHUFFLE(2, 2, 2, 2)), otherRow2)));
	__m128 outRow2 = _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(thisRow2, thisRow2, _MM_SHUFFLE(0, 0, 0, 0)), otherRow0), _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(thisRow2, thisRow2, _MM_SHUFFLE(1, 1, 1, 1)), otherRow1), _mm_mul_ps(_mm_shuffle_ps(thisRow2, thisRow2, _MM_SHUFFLE(2, 2, 2, 2)), otherRow2)));

	// add in translation vector
	std::uint32_t arrComponentMask[4] = { 0x0, 0x0, 0x0, 0xFFFFFFFF };
	outRow0 = _mm_add_ps(outRow0, _mm_and_ps(thisRow0, std::bit_cast<__m128>(arrComponentMask)));
	outRow1 = _mm_add_ps(outRow1, _mm_and_ps(thisRow1, std::bit_cast<__m128>(arrComponentMask)));
	outRow2 = _mm_add_ps(outRow2, _mm_and_ps(thisRow2, std::bit_cast<__m128>(arrComponentMask)));

	_mm_store_ps(matOutput.arrData[0], outRow0);
	_mm_store_ps(matOutput.arrData[1], outRow1);
	_mm_store_ps(matOutput.arrData[2], outRow2);
	return matOutput;
}




ViewMatrix_t::ViewMatrix_t(
	const float m00, const float m01, const float m02, const float m03,
	const float m10, const float m11, const float m12, const float m13,
	const float m20, const float m21, const float m22, const float m23,
	const float m30, const float m31, const float m32, const float m33)
{
	arrData[0][0] = m00;
	arrData[0][1] = m01;
	arrData[0][2] = m02;
	arrData[0][3] = m03;
	arrData[1][0] = m10;
	arrData[1][1] = m11;
	arrData[1][2] = m12;
	arrData[1][3] = m13;
	arrData[2][0] = m20;
	arrData[2][1] = m21;
	arrData[2][2] = m22;
	arrData[2][3] = m23;
	arrData[3][0] = m30;
	arrData[3][1] = m31;
	arrData[3][2] = m32;
	arrData[3][3] = m33;
}

ViewMatrix_t::ViewMatrix_t(const Matrix3x4_t& matFrom, const Vector4D_t& vecAdditionalRow)
{
	arrData[0][0] = matFrom.arrData[0][0];
	arrData[0][1] = matFrom.arrData[0][1];
	arrData[0][2] = matFrom.arrData[0][2];
	arrData[0][3] = matFrom.arrData[0][3];
	arrData[1][0] = matFrom.arrData[1][0];
	arrData[1][1] = matFrom.arrData[1][1];
	arrData[1][2] = matFrom.arrData[1][2];
	arrData[1][3] = matFrom.arrData[1][3];
	arrData[2][0] = matFrom.arrData[2][0];
	arrData[2][1] = matFrom.arrData[2][1];
	arrData[2][2] = matFrom.arrData[2][2];
	arrData[2][3] = matFrom.arrData[2][3];
	arrData[3][0] = vecAdditionalRow.x;
	arrData[3][1] = vecAdditionalRow.y;
	arrData[3][2] = vecAdditionalRow.z;
	arrData[3][3] = vecAdditionalRow.w;
}

[[nodiscard]] float* ViewMatrix_t::operator[](const int nIndex)
{
	return arrData[nIndex];
}

[[nodiscard]] const float* ViewMatrix_t::operator[](const int nIndex) const
{
	return arrData[nIndex];
}

[[nodiscard]] const bool ViewMatrix_t::operator==(const ViewMatrix_t& viewOther) const
{
	return (
		arrData[0][0] == viewOther.arrData[0][0] && arrData[0][1] == viewOther.arrData[0][1] && arrData[0][2] == viewOther.arrData[0][2] && arrData[0][3] == viewOther.arrData[0][3] &&
		arrData[1][0] == viewOther.arrData[1][0] && arrData[1][1] == viewOther.arrData[1][1] && arrData[1][2] == viewOther.arrData[1][2] && arrData[1][3] == viewOther.arrData[1][3] &&
		arrData[2][0] == viewOther.arrData[2][0] && arrData[2][1] == viewOther.arrData[2][1] && arrData[2][2] == viewOther.arrData[2][2] && arrData[2][3] == viewOther.arrData[2][3] &&
		arrData[3][0] == viewOther.arrData[3][0] && arrData[3][1] == viewOther.arrData[3][1] && arrData[3][2] == viewOther.arrData[3][2] && arrData[3][3] == viewOther.arrData[3][3]);
}

[[nodiscard]] const Matrix3x4_t& ViewMatrix_t::As3x4() const
{
	return *reinterpret_cast<const Matrix3x4_t*>(this);
}

[[nodiscard]] Matrix3x4_t& ViewMatrix_t::As3x4()
{
	return *reinterpret_cast<Matrix3x4_t*>(this);
}

ViewMatrix_t& ViewMatrix_t::operator+=(const ViewMatrix_t& matAdd)
{
	for (std::uint8_t c = 0U; c < 4U; c++)
	{
		for (std::uint8_t r = 0U; r < 4U; r++)
			arrData[c][r] += matAdd[c][r];
	}

	return *this;
}

ViewMatrix_t& ViewMatrix_t::operator-=(const ViewMatrix_t& matSubtract)
{
	for (std::uint8_t c = 0U; c < 4U; c++)
	{
		for (std::uint8_t r = 0U; r < 4U; r++)
			arrData[c][r] -= matSubtract[c][r];
	}

	return *this;
}

[[nodiscard]] Vector4D_t ViewMatrix_t::GetRow(const int nIndex) const
{
	return { arrData[nIndex][0], arrData[nIndex][1], arrData[nIndex][2], arrData[nIndex][3] };
}

[[nodiscard]] Vector4D_t ViewMatrix_t::GetColumn(const int nIndex) const
{
	return { arrData[0][nIndex], arrData[1][nIndex], arrData[2][nIndex], arrData[3][nIndex] };
}

void ViewMatrix_t::Identity()
{
	for (std::uint8_t c = 0U; c < 4U; c++)
	{
		for (std::uint8_t r = 0U; r < 4U; r++)
			arrData[c][r] = (c == r) ? 1.0f : 0.0f;
	}
}


/// concatenate transformations of two matrices into one
/// @returns: matrix with concatenated transformations
[[nodiscard]] ViewMatrix_t ViewMatrix_t::ConcatTransforms(const ViewMatrix_t& matOther) const
{
	return {
		arrData[0][0] * matOther.arrData[0][0] + arrData[0][1] * matOther.arrData[1][0] + arrData[0][2] * matOther.arrData[2][0] + arrData[0][3] * matOther.arrData[3][0],
		arrData[0][0] * matOther.arrData[0][1] + arrData[0][1] * matOther.arrData[1][1] + arrData[0][2] * matOther.arrData[2][1] + arrData[0][3] * matOther.arrData[3][1],
		arrData[0][0] * matOther.arrData[0][2] + arrData[0][1] * matOther.arrData[1][2] + arrData[0][2] * matOther.arrData[2][2] + arrData[0][3] * matOther.arrData[3][2],
		arrData[0][0] * matOther.arrData[0][3] + arrData[0][1] * matOther.arrData[1][3] + arrData[0][2] * matOther.arrData[2][3] + arrData[0][3] * matOther.arrData[3][3],

		arrData[1][0] * matOther.arrData[0][0] + arrData[1][1] * matOther.arrData[1][0] + arrData[1][2] * matOther.arrData[2][0] + arrData[1][3] * matOther.arrData[3][0],
		arrData[1][0] * matOther.arrData[0][1] + arrData[1][1] * matOther.arrData[1][1] + arrData[1][2] * matOther.arrData[2][1] + arrData[1][3] * matOther.arrData[3][1],
		arrData[1][0] * matOther.arrData[0][2] + arrData[1][1] * matOther.arrData[1][2] + arrData[1][2] * matOther.arrData[2][2] + arrData[1][3] * matOther.arrData[3][2],
		arrData[1][0] * matOther.arrData[0][3] + arrData[1][1] * matOther.arrData[1][3] + arrData[1][2] * matOther.arrData[2][3] + arrData[1][3] * matOther.arrData[3][3],

		arrData[2][0] * matOther.arrData[0][0] + arrData[2][1] * matOther.arrData[1][0] + arrData[2][2] * matOther.arrData[2][0] + arrData[2][3] * matOther.arrData[3][0],
		arrData[2][0] * matOther.arrData[0][1] + arrData[2][1] * matOther.arrData[1][1] + arrData[2][2] * matOther.arrData[2][1] + arrData[2][3] * matOther.arrData[3][1],
		arrData[2][0] * matOther.arrData[0][2] + arrData[2][1] * matOther.arrData[1][2] + arrData[2][2] * matOther.arrData[2][2] + arrData[2][3] * matOther.arrData[3][2],
		arrData[2][0] * matOther.arrData[0][3] + arrData[2][1] * matOther.arrData[1][3] + arrData[2][2] * matOther.arrData[2][3] + arrData[2][3] * matOther.arrData[3][3],

		arrData[3][0] * matOther.arrData[0][0] + arrData[3][1] * matOther.arrData[1][0] + arrData[3][2] * matOther.arrData[2][0] + arrData[3][3] * matOther.arrData[3][0],
		arrData[3][0] * matOther.arrData[0][1] + arrData[3][1] * matOther.arrData[1][1] + arrData[3][2] * matOther.arrData[2][1] + arrData[3][3] * matOther.arrData[3][1],
		arrData[3][0] * matOther.arrData[0][2] + arrData[3][1] * matOther.arrData[1][2] + arrData[3][2] * matOther.arrData[2][2] + arrData[3][3] * matOther.arrData[3][2],
		arrData[3][0] * matOther.arrData[0][3] + arrData[3][1] * matOther.arrData[1][3] + arrData[3][2] * matOther.arrData[2][3] + arrData[3][3] * matOther.arrData[3][3]
	};
}


Matrix2x4_t::Matrix2x4_t(Matrix2x4_t* m) {
	_11 = m->_11;
	_12 = m->_12;
	_13 = m->_13;
	_14 = m->_14;
	_21 = m->_21;
	_22 = m->_22;
	_23 = m->_23;
	_24 = m->_24;
}
Matrix2x4_t::Matrix2x4_t() {
	_11 = 0.0f;
	_12 = 0.0f;
	_13 = 0.0f;
	_14 = 0.0f;
	_21 = 0.0f;
	_22 = 0.0f;
	_23 = 0.0f;
	_24 = 0.0f;
}
Matrix2x4_t::~Matrix2x4_t() {
}
Matrix3x4_t Matrix2x4_t::TranslateToMatrix3x4()
{
	Matrix3x4_t matrix = Matrix3x4_t();
	Vector4D_t vecRotation = Vector4D_t();
	Vector vecPosition = Vector();

	vecRotation.x = this->_21; //rot.x
	vecRotation.y = this->_22; //rot.y
	vecRotation.z = this->_23; //rot.z
	vecRotation.w = this->_24; //rot.w

	vecPosition.x = this->_11; //bonepos.x
	vecPosition.y = this->_12; //bonepos.y
	vecPosition.z = this->_13; //bonepos.z

	matrix[0][0] = 1.0f - 2.0f * vecRotation.y * vecRotation.y - 2.0f * vecRotation.z * vecRotation.z;
	matrix[1][0] = 2.0f * vecRotation.x * vecRotation.y + 2.0f * vecRotation.w * vecRotation.z;
	matrix[2][0] = 2.0f * vecRotation.x * vecRotation.z - 2.0f * vecRotation.w * vecRotation.y;

	matrix[0][1] = 2.0f * vecRotation.x * vecRotation.y - 2.0f * vecRotation.w * vecRotation.z;
	matrix[1][1] = 1.0f - 2.0f * vecRotation.x * vecRotation.x - 2.0f * vecRotation.z * vecRotation.z;
	matrix[2][1] = 2.0f * vecRotation.y * vecRotation.z + 2.0f * vecRotation.w * vecRotation.x;

	matrix[0][2] = 2.0f * vecRotation.x * vecRotation.z + 2.0f * vecRotation.w * vecRotation.y;
	matrix[1][2] = 2.0f * vecRotation.y * vecRotation.z - 2.0f * vecRotation.w * vecRotation.x;
	matrix[2][2] = 1.0f - 2.0f * vecRotation.x * vecRotation.x - 2.0f * vecRotation.y * vecRotation.y;

	matrix[0][3] = vecPosition.x;
	matrix[1][3] = vecPosition.y;
	matrix[2][3] = vecPosition.z;

	return matrix;
}
Vector Matrix2x4_t::GetOrigin() const {
	return Vector(_11, _12, _13);
}

Vector Matrix2x4_t::GetOrigin(int nIndex) const {
	return Vector(this[nIndex]._11, this[nIndex]._12, this[nIndex]._13);
}

Vector Matrix2x4_t::TransformPosition(const Vector& local) const {
	return Vector3{
		_11 * local.x + _12 * local.y + _13 * local.z + _14,
		_21 * local.x + _22 * local.y + _23 * local.z + _24,
		0.0f // <- you don’t have row 3? If your matrix is really 2x4, Z may be missing
	};
}

Vector4D_t Matrix2x4_t::GetRotation() const {
	return Vector4D_t(_21, _22, _23, _24);
}

Vector4D_t Matrix2x4_t::GetRotation(int nIndex) const {
	return Vector4D_t(this[nIndex]._21, this[nIndex]._22, this[nIndex]._23, this[nIndex]._24);
}
