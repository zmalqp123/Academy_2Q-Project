#pragma once
#include <D2D1Helper.h>
#include <math.h>

class Vector2 : public D2D_VECTOR_2F {
public:
	Vector2() = default;

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2(const D2D_VECTOR_2F& vector)
	{
		this->x = vector.x;
		this->y = vector.y;
	}

	Vector2(const Vector2&) = default;

	Vector2& operator=(const Vector2&) = default;

	Vector2(Vector2&&) = default;

	Vector2& operator=(Vector2&&) = default;

	~Vector2() = default;

	Vector2 operator+(const Vector2& vector) const
	{
		return Vector2(this->x + vector.x, this->y + vector.y);
	}

	Vector2 operator-(const Vector2& vector) const
	{
		return Vector2(this->x - vector.x, this->y - vector.y);
	}

	Vector2 operator*(float scalar) const
	{
		return Vector2(this->x * scalar, this->y * scalar);
	}

	Vector2 operator/(float scalar) const
	{
		return Vector2(this->x / scalar, this->y / scalar);
	}

	Vector2& operator+=(const Vector2& vector)
	{
		this->x += vector.x;
		this->y += vector.y;

		return *this;
	}

	Vector2& operator-=(const Vector2& vector)
	{
		this->x -= vector.x;
		this->y -= vector.y;
		return *this;
	}

	Vector2& operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		return *this;
	}

	Vector2& operator/=(float scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		return *this;
	}

	bool operator==(const Vector2& vector) const
	{
		return (this->x == vector.x && this->y == vector.y);
	}

	float Length() const
	{
		return sqrtf(this->x * this->x + this->y * this->y);
	}

	float LengthSquared() const
	{
		return (this->x * this->x + this->y * this->y);
	}

	float Normalize()
	{
		float length = Length();

		if (length > 0.0f)
		{
			float invLength = 1.0f / length;
			this->x *= invLength;
			this->y *= invLength;
		}

		return length;
	}

	static float DotProduct(const Vector2& a, const Vector2& b) {
		return a.x * b.x + a.y * b.y;
	}

	static float CrossProduct(const Vector2& a, const Vector2& b) {
		return a.x * b.y - a.y * b.x;
	}
};

class Vector3 : public D2D_VECTOR_3F
{
public:
	Vector3() = default;

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3(const D2D_VECTOR_3F& vector)
	{
		this->x = vector.x;
		this->y = vector.y;
		this->z = vector.z;
	}

	Vector3(const Vector3&) = default;

	Vector3& operator=(const Vector3&) = default;

	Vector3(Vector3&&) = default;

	Vector3& operator=(Vector3&&) = default;

	~Vector3() = default;

	Vector3 operator+(const Vector3& vector) const
	{
		return Vector3(this->x + vector.x, this->y + vector.y, this->z + vector.z);
	}

	Vector3 operator-(const Vector3& vector) const
	{
		return Vector3(this->x - vector.x, this->y - vector.y, this->z - vector.z);
	}

	Vector3 operator*(float scalar) const
	{
		return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
	}

	Vector3 operator/(float scalar) const
	{
		return Vector3(this->x / scalar, this->y / scalar, this->z / scalar);
	}

	Vector3& operator+=(const Vector3& vector)
	{
		this->x += vector.x;
		this->y += vector.y;
		this->z += vector.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& vector)
	{
		this->x -= vector.x;
		this->y -= vector.y;
		this->z -= vector.z;
		return *this;
	}

	Vector3& operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		return *this;
	}
	Vector3& operator/=(float scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;
		return *this;
	}

	bool operator==(const Vector3& vector) const
	{
		return (this->x == vector.x && this->y == vector.y && this->z == vector.z);
	}

	float Length() const
	{
		return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	float LengthSquared() const
	{
		return (this->x * this->x + this->y * this->y + this->z * this->z);
	}

	float Normalize()
	{
		float length = Length();

		if (length > 0.0f)
		{
			float invLength = 1.0f / length;
			this->x *= invLength;
			this->y *= invLength;
			this->z *= invLength;
		}
		return length;
	}

};

//현재 사용x
class Matrix3X2 : public D2D1_MATRIX_3X2_F {
public:
	Matrix3X2() = default;

	Matrix3X2(float _11, float _12, float _21, float _22, float _31, float _32) {
		this->_11 = _11;
		this->_12 = _12;
		this->_21 = _21;
		this->_22 = _22;
		this->_31 = _31;
		this->_32 = _32;
	}

	Matrix3X2(const Matrix3X2& matrix3x2) = default;

	Matrix3X2& operator=(const Matrix3X2&) = default;

	Matrix3X2(Matrix3X2&&) = default;

	Matrix3X2& operator=(Matrix3X2&&) = default;

	~Matrix3X2() = default;

	Matrix3X2 operator+(const Matrix3X2& matrix) const {
		return Matrix3X2(
			this->_11 + matrix._11,
			this->_12 + matrix._12,
			this->_21 + matrix._21,
			this->_22 + matrix._22,
			this->_31 + matrix._31,
			this->_32 + matrix._32
		);
	}

	Matrix3X2 operator-(const Matrix3X2& matrix) const {
		return Matrix3X2(
			this->_11 - matrix._11,
			this->_12 - matrix._12,
			this->_21 - matrix._21,
			this->_22 - matrix._22,
			this->_31 - matrix._31,
			this->_32 - matrix._32
		);
	}
};