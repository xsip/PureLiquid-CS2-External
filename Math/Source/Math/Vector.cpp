#include <Math/Core.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Math/QAngle.h>
#include <algorithm>

constexpr Vector2D_t::Vector2D_t(const float x, const float y) :
	x(x), y(y) {
}

[[nodiscard]] bool Vector2D_t::IsZero() const
{
	// @note: to make this implementation right, we should use fpclassify here, but game aren't doing same, probably it's better to keep this same, just ensure that it will be compiled same
	return (this->x == 0.0f && this->y == 0.0f);
}


constexpr Vector::Vector(const float x, const float y, const float z) :
	x(x), y(y), z(z) {
}

constexpr Vector::Vector(const float* arrVector) :
	x(arrVector[0]), y(arrVector[1]), z(arrVector[2]) {
}

constexpr Vector::Vector(const Vector2D_t& vecBase2D) :
	x(vecBase2D.x), y(vecBase2D.y) {
}

void Vector::AngleVectors(Vector* forward, Vector* right, Vector* up)
{
	float sr, sp, sy, cr, cp, cy;

	MATH::SinCos(DEG2RAD(this->x), &sp, &cp);
	MATH::SinCos(DEG2RAD(this->y), &sy, &cy);
	MATH::SinCos(DEG2RAD(this->z), &sr, &cr);

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;


	right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
	right->y = (-1 * sr * sp * sy + -1 * cr * cy);
	right->z = -1 * sr * cp;

	up->x = (cr * sp * cy + -sr * -sy);
	up->y = (cr * sp * sy + -sr * cy);
	up->z = cr * cp;

}


[[nodiscard]] float& Vector::operator[](const int nIndex)
{
	return reinterpret_cast<float*>(this)[nIndex];
}

[[nodiscard]] const float& Vector::operator[](const int nIndex) const
{
	return reinterpret_cast<const float*>(this)[nIndex];
}


bool Vector::operator==(const Vector& vecBase) const
{
	return this->IsEqual(vecBase);
}

bool Vector::operator!=(const Vector& vecBase) const
{
	return !this->IsEqual(vecBase);
}

constexpr Vector& Vector::operator=(const Vector& vecBase)
{
	this->x = vecBase.x;
	this->y = vecBase.y;
	this->z = vecBase.z;
	return *this;
}

constexpr Vector& Vector::operator=(const Vector2D_t& vecBase2D)
{
	this->x = vecBase2D.x;
	this->y = vecBase2D.y;
	this->z = 0.0f;
	return *this;
}


constexpr Vector& Vector::operator+=(const Vector& vecBase)
{
	this->x += vecBase.x;
	this->y += vecBase.y;
	this->z += vecBase.z;
	return *this;
}

constexpr Vector& Vector::operator-=(const Vector& vecBase)
{
	this->x -= vecBase.x;
	this->y -= vecBase.y;
	this->z -= vecBase.z;
	return *this;
}

constexpr Vector& Vector::operator*=(const Vector& vecBase)
{
	this->x *= vecBase.x;
	this->y *= vecBase.y;
	this->z *= vecBase.z;
	return *this;
}

constexpr Vector& Vector::operator/=(const Vector& vecBase)
{
	this->x /= vecBase.x;
	this->y /= vecBase.y;
	this->z /= vecBase.z;
	return *this;
}

constexpr Vector& Vector::operator+=(const float flAdd)
{
	this->x += flAdd;
	this->y += flAdd;
	this->z += flAdd;
	return *this;
}

constexpr Vector& Vector::operator-=(const float flSubtract)
{
	this->x -= flSubtract;
	this->y -= flSubtract;
	this->z -= flSubtract;
	return *this;
}

constexpr Vector& Vector::operator*=(const float flMultiply)
{
	this->x *= flMultiply;
	this->y *= flMultiply;
	this->z *= flMultiply;
	return *this;
}

constexpr Vector& Vector::operator/=(const float flDivide)
{
	this->x /= flDivide;
	this->y /= flDivide;
	this->z /= flDivide;
	return *this;
}



constexpr Vector& Vector::operator-()
{
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;
	return *this;
}

constexpr Vector Vector::operator-() const
{
	return { -this->x, -this->y, -this->z };
}


Vector Vector::operator+(const Vector& vecAdd) const
{
	return { this->x + vecAdd.x, this->y + vecAdd.y, this->z + vecAdd.z };
}

Vector Vector::operator-(const Vector& vecSubtract) const
{
	return { this->x - vecSubtract.x, this->y - vecSubtract.y, this->z - vecSubtract.z };
}

Vector Vector::operator*(const Vector& vecMultiply) const
{
	return { this->x * vecMultiply.x, this->y * vecMultiply.y, this->z * vecMultiply.z };
}

Vector Vector::operator/(const Vector& vecDivide) const
{
	return { this->x / vecDivide.x, this->y / vecDivide.y, this->z / vecDivide.z };
}

Vector Vector::operator+(const float flAdd) const
{
	return { this->x + flAdd, this->y + flAdd, this->z + flAdd };
}

Vector Vector::operator-(const float flSubtract) const
{
	return { this->x - flSubtract, this->y - flSubtract, this->z - flSubtract };
}

Vector Vector::operator*(const float flMultiply) const
{
	return { this->x * flMultiply, this->y * flMultiply, this->z * flMultiply };
}

Vector Vector::operator/(const float flDivide) const
{
	return { this->x / flDivide, this->y / flDivide, this->z / flDivide };
}


/// @returns: true if each component of the vector is finite, false otherwise
[[nodiscard]] bool Vector::IsValid() const
{
	return std::isfinite(this->x) && std::isfinite(this->y) && std::isfinite(this->z);
}

constexpr void Vector::Invalidate()
{
	this->x = this->y = this->z = std::numeric_limits<float>::infinity();
}

/// @returns: true if each component of the vector equals to another, false otherwise
[[nodiscard]] bool Vector::IsEqual(const Vector& vecEqual, const float flErrorMargin) const
{
	return (std::fabsf(this->x - vecEqual.x) < flErrorMargin && std::fabsf(this->y - vecEqual.y) < flErrorMargin && std::fabsf(this->z - vecEqual.z) < flErrorMargin);
}

/// @returns: true if each component of the vector equals to zero, false otherwise
[[nodiscard]] bool Vector::IsZero() const
{
	// @note: to make this implementation right, we should use fpclassify here, but game aren't doing same, probably it's better to keep this same, just ensure that it will be compiled same
	return (this->x == 0.0f && this->y == 0.0f && this->z == 0.0f);
}

[[nodiscard]] float Vector::Length() const
{
	return std::sqrtf(this->LengthSqr());
}

[[nodiscard]] constexpr float Vector::LengthSqr() const
{
	return DotProduct(*this);
}

[[nodiscard]] float Vector::Length2D() const
{
	return std::sqrtf(this->Length2DSqr());
}

[[nodiscard]] constexpr float Vector::Length2DSqr() const
{
	return (this->x * this->x + this->y * this->y);
}

[[nodiscard]] float Vector::DistTo(const Vector& vecEnd) const
{
	return (*this - vecEnd).Length();
}

[[nodiscard]] constexpr float Vector::DistToSqr(const Vector& vecEnd) const
{
	return (*this - vecEnd).LengthSqr();
}

/// normalize magnitude of each component of the vector
/// @returns: length of the vector
float Vector::NormalizeInPlace()
{
	const float flLength = this->Length();
	const float flRadius = 1.0f / (flLength + std::numeric_limits<float>::epsilon());

	this->x *= flRadius;
	this->y *= flRadius;
	this->z *= flRadius;

	return flLength;
}

/// normalize magnitude of each component of the vector
/// @returns: copy of the vector with normalized components
[[nodiscard]] Vector Vector::Normalized() const
{
	Vector vecOut = *this;
	vecOut.NormalizeInPlace();
	return vecOut;
}

[[nodiscard]] constexpr float Vector::DotProduct(const Vector& vecDot) const
{
	return (this->x * vecDot.x + this->y * vecDot.y + this->z * vecDot.z);
}

[[nodiscard]] float Vector::DotProductSIMD( const Vector& b) const {
	__m128 va = _mm_set_ps(0.0f, this->z, this->y, this->x);
	__m128 vb = _mm_set_ps(0.0f, b.z, b.y, b.x);
	__m128 mul = _mm_mul_ps(va, vb);
	__m128 shuf1 = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 1, 0, 3));
	__m128 sum1 = _mm_add_ps(mul, shuf1);
	__m128 shuf2 = _mm_movehl_ps(sum1, sum1);
	__m128 sum2 = _mm_add_ss(sum1, shuf2);
	return _mm_cvtss_f32(sum2);
}

[[nodiscard]] constexpr Vector Vector::CrossProduct(const Vector& vecCross) const
{
	return { this->y * vecCross.z - this->z * vecCross.y, this->z * vecCross.x - this->x * vecCross.z, this->x * vecCross.y - this->y * vecCross.x };
}

[[nodiscard]] Vector2D_t Vector::ToVector2D() const
{
	return { this->x, this->y };
}

/// convert forward direction vector to other direction vectors
/// @param[out] pvecRight [optional] output for converted right vector
/// @param[out] pvecUp [optional] output for converted up vector
void Vector::ToDirections(Vector* pvecRight, Vector* pvecUp) const
{
	if (std::fabsf(this->x) < 1e-6f && std::fabsf(this->y) < 1e-6f)
	{
		// pitch 90 degrees up/down from identity
		if (pvecRight != nullptr)
		{
			pvecRight->x = 0.0f;
			pvecRight->y = -1.0f;
			pvecRight->z = 0.0f;
		}

		if (pvecUp != nullptr)
		{
			pvecUp->x = -this->z;
			pvecUp->y = 0.0f;
			pvecUp->z = 0.0f;
		}
	}
	else
	{
		if (pvecRight != nullptr)
		{
			pvecRight->x = this->y;
			pvecRight->y = -this->x;
			pvecRight->z = 0.0f;
			pvecRight->NormalizeInPlace();
		}

		if (pvecUp != nullptr)
		{
			pvecUp->x = (-this->x) * this->z;
			pvecUp->y = -(this->y * this->z);
			pvecUp->z = this->y * this->y - (-this->x) * this->x;
			pvecUp->NormalizeInPlace();
		}
	}
}


[[nodiscard]] Vector Vector::Transform(const Matrix3x4_t& matTransform) const
{
	return {
		this->DotProduct(matTransform[0]) + matTransform[0][3],
		this->DotProduct(matTransform[1]) + matTransform[1][3],
		this->DotProduct(matTransform[2]) + matTransform[2][3]
	};
}
#include <numbers>
[[nodiscard]] QAngle_t Vector::RelativeAngle() const
{
	return {
		std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
		std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
		0.0f
	};
}

#include <emmintrin.h> // SSE2

[[nodiscard]] bool Vector::ToScreenSSE(const ViewMatrix_t& vm, int screenWidth, int screenHeight, Vector& out) const
{
	// Load point into SSE register with w=1 for translation
	__m128 vec = _mm_set_ps(1.0f, z, y, x); // [w, z, y, x]

	// Load matrix rows
	const float* m0 = vm[0]; // row 0
	const float* m1 = vm[1]; // row 1
	const float* m3 = vm[3]; // row 3 (for w)

	// Compute w = dot(row3, [x,y,z,1])
	__m128 mulW = _mm_mul_ps(_mm_loadu_ps(m3), vec);
	__m128 shufW = _mm_shuffle_ps(mulW, mulW, _MM_SHUFFLE(2, 3, 0, 1));
	__m128 sumW = _mm_add_ps(mulW, shufW);
	shufW = _mm_movehl_ps(shufW, sumW);
	sumW = _mm_add_ss(sumW, shufW);
	float w = _mm_cvtss_f32(sumW);

	if (w <= 0.001f)
		return false;

	float invW = 1.0f / w;

	// Compute projX = dot(row0, [x,y,z,1]) * invW
	__m128 mul0 = _mm_mul_ps(_mm_loadu_ps(m0), vec);
	__m128 shuf0 = _mm_shuffle_ps(mul0, mul0, _MM_SHUFFLE(2, 3, 0, 1));
	__m128 sum0 = _mm_add_ps(mul0, shuf0);
	shuf0 = _mm_movehl_ps(shuf0, sum0);
	sum0 = _mm_add_ss(sum0, shuf0);
	float projX = _mm_cvtss_f32(sum0) * invW;

	// Compute projY = dot(row1, [x,y,z,1]) * invW
	__m128 mul1 = _mm_mul_ps(_mm_loadu_ps(m1), vec);
	__m128 shuf1 = _mm_shuffle_ps(mul1, mul1, _MM_SHUFFLE(2, 3, 0, 1));
	__m128 sum1 = _mm_add_ps(mul1, shuf1);
	shuf1 = _mm_movehl_ps(shuf1, sum1);
	sum1 = _mm_add_ss(sum1, shuf1);
	float projY = _mm_cvtss_f32(sum1) * invW;

	// Convert to screen space
	const float halfWidth = static_cast<float>(screenWidth) * 0.5f;
	const float halfHeight = static_cast<float>(screenHeight) * 0.5f;

	out.x = halfWidth + projX * halfWidth;
	out.y = halfHeight - projY * halfHeight; // match your scalar Y-axis convention

	return true;
}


[[nodiscard]] bool Vector::ToScreen(ViewMatrix_t vm, int screenWidth, int screenHeight, Vector& out) const
{
	const Matrix3x4_t& w2s = vm.As3x4();

	const float w3 = (w2s[3][0] * x + w2s[3][1] * y + w2s[3][2] * z + w2s[3][3]);

	if (w3 > 0.001f)
	{
		const float flsw = static_cast<float>(screenWidth);
		const float flsh = static_cast<float>(screenHeight);
		const float fl1dbw = 1.0f / w3;

		out.x = static_cast<int>((flsw / 2.0f) + (0.5f * ((w2s[0][0] * x + w2s[0][1] * y + w2s[0][2] * z + w2s[0][3]) * fl1dbw) * flsw + 0.5f));
		out.y = static_cast<int>((flsh / 2.0f) - (0.5f * ((w2s[1][0] * x + w2s[1][1] * y + w2s[1][2] * z + w2s[1][3]) * fl1dbw) * flsh + 0.5f));

		return true;
	}

	return false;

	auto w2 = vm[3][0] * x +
		vm[3][1] * y +
		vm[3][2] * z +
		vm[3][3];

	if (w2 < 0.01f)
		return false;

	auto mulRow0 = vm[0][0] * x +
		vm[0][1] * y +
		vm[0][2] * z +
		vm[0][3];

	auto mulRow1 = vm[1][0] * x +
		vm[1][1] * y +
		vm[1][2] * z +
		vm[1][3];



	out.x = (screenWidth / 2.0f) * (1.0f + mulRow0 / w2);
	out.y = (screenHeight / 2.0f) * (1.0f - mulRow1 / w2);

	return true;

	const float w = (vm)[3][0] * x + (vm)[3][1] * y + (vm)[3][2] * z + (vm)[3][3];

	if (w <= 0.01)
		return false;

	const float invW = 1.0f / w;

	out.x = (screenWidth / 2) + (((vm)[0][0] * x + (vm)[0][1] * y + (vm)[0][2] * z + (vm)[0][3]) * invW * (screenWidth / 2));
	out.y = (screenHeight / 2) - (((vm)[1][0] * x + (vm)[1][1] * y + (vm)[1][2] * z + (vm)[1][3]) * invW * (screenHeight / 2));

	return true;

}

[[nodiscard]] bool Vector::ToScreenDota(ViewMatrix_t view, int screenWidth, int screenHeight, Vector& out) const
{
	// world * matrix
	float clipX =
		view[0][0] * x +
		view[0][1] * y +
		view[0][2] * z +
		view[0][3];

	float clipY =
		view[1][0] * x +
		view[1][1] * y +
		view[1][2] * z +
		view[1][3];

	float clipW =
		view[3][0] * x +
		view[3][1] * y +
		view[3][2] * z +
		view[3][3];

	// avoid divide-by-zero / behind camera
	// if (clipW < 0.001f)
		// return false;

	float invW = 1.0f / clipW;
	float ndcX = clipX * invW;
	float ndcY = clipY * invW;

	// convert from normalized device coords to screen coords
	out.x = (screenWidth * 0.5f) + (ndcX * screenWidth * 0.5f);
	out.y = (screenHeight * 0.5f) - (ndcY * screenHeight * 0.5f); // note the minus for y

	return true;
}

[[nodiscard]] QAngle_t Vector::ToAngles() const
{
	float flPitch, flYaw;
	if (this->x == 0.0f && this->y == 0.0f)
	{
		flPitch = (this->z > 0.0f) ? 270.f : 90.f;
		flYaw = 0.0f;
	}
	else
	{
		flPitch = M_RAD2DEG(std::atan2f(-this->z, this->Length2D()));

		if (flPitch < 0.f)
			flPitch += 360.f;

		flYaw = M_RAD2DEG(std::atan2f(this->y, this->x));

		if (flYaw < 0.f)
			flYaw += 360.f;
	}

	return { flPitch, flYaw, 0.0f };
}

[[nodiscard]] Matrix3x4_t Vector::ToMatrix() const
{
	Vector vecRight = {}, vecUp = {};
	this->ToDirections(&vecRight, &vecUp);

	Matrix3x4a_t matOutput = {};
	matOutput.SetForward(*this);
	matOutput.SetLeft(-vecRight);
	matOutput.SetUp(vecUp);
	return matOutput;
}

Vector Vector::ComponentMin(const Vector3& other) const {
	return Vector3{
		std::min(x, other.x),
		std::min(y, other.y),
		std::min(z, other.z)
	};
}

// Returns a new vector with the max of each component
Vector Vector::ComponentMax(const Vector3& other) const {
	return Vector3{
		std::max(x, other.x),
		std::max(y, other.y),
		std::max(z, other.z)
	};
}

Vector Vector4D_t::ToVector() {
	return { this->x,this->y,this->z };
}

VectorAligned_t::VectorAligned_t(const Vector& vecBase)
{
	this->x = vecBase.x;
	this->y = vecBase.y;
	this->z = vecBase.z;
	this->w = 0.0f;
}

constexpr VectorAligned_t& VectorAligned_t::operator=(const Vector& vecBase)
{
	this->x = vecBase.x;
	this->y = vecBase.y;
	this->z = vecBase.z;
	this->w = 0.0f;
	return *this;
}
