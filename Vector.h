#pragma once
#include <math.h>
#include <stdlib.h>
#include <intrin.h>


#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)

#define FastSqrt(x)			(sqrt)(x)

#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h

#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.

#define M_PHI		1.61803398874989484820 // golden ratio

// NJS: Inlined to prevent floats from being autopromoted to doubles, as with the old system.
#ifndef RAD2DEG
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif

struct Matrix3x3
{
	float M11; //a
	float M12; //b
	float M13; //c
	float M21; //d
	float M22; //e
	float M23; //f
	float M31; //g
	float M32; //h
	float M33; //i
	Matrix3x3()
		: M11(0), M12(0), M13(0), M21(0), M22(0), M23(0), M31(0), M32(0), M33(0) {}
	Matrix3x3(const float _00, const float _01, const float _02, const float _10, const float _11, const float _12, const float _20, const float _21, const float _22)
		: M11(_00), M12(_02), M13(_02), M21(_10), M22(_12), M23(_12), M31(_20), M32(_21), M33(_22) {}

	Matrix3x3 Inverse()
	{
		Matrix3x3 result = Matrix3x3(0, 0, 0, 0, 0, 0, 0, 0, 0);
		float d11 = M22 * M33 + M23 * -M32;
		float d12 = M21 * M33 + M23 * -M31;
		float d13 = M21 * M32 + M22 * -M31;

		float det = M11 * d11 - M12 * d12 + M13 * d13;
		if (std::abs(det) == 0.0f)
		{
			return result;
		}

		det = 1.f / det;

		float d21 = M12 * M33 + M13 * -M32;
		float d22 = M11 * M33 + M13 * -M31;
		float d23 = M11 * M32 + M12 * -M31;

		float d31 = (M12 * M23) - (M13 * M22);
		float d32 = (M11 * M23) - (M13 * M21);
		float d33 = (M11 * M22) - (M12 * M21);

		result.M11 = +d11 * det; result.M12 = -d21 * det; result.M13 = +d31 * det;
		result.M21 = -d12 * det; result.M22 = +d22 * det; result.M23 = -d32 * det;
		result.M31 = +d13 * det; result.M32 = -d23 * det; result.M33 = +d33 * det;

		return result;
	}
};

#define ALIGN16 DECL_ALIGN(16)
#define VALVE_RAND_MAX 0x7fff
#define VectorExpand(v) (v).x, (v).y, (v).z

class Vector
{
public:
	float x, y, z;
	Vector(void);
	Vector(float X, float Y, float Z);
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	bool IsValid() const;
	float operator[](int i) const;
	float& operator[](int i);
	inline void Zero();
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;
	inline Vector& operator+=(const Vector& v);
	inline Vector& operator-=(const Vector& v);
	inline Vector& operator*=(const Vector& v);
	inline Vector& operator*=(float s);
	inline Vector& operator/=(const Vector& v);
	inline Vector& operator/=(float s);
	inline Vector& operator+=(float fl);
	inline Vector& operator-=(float fl);
	inline float	Length() const;
	inline float LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (x * x + y * y + z * z);
	}
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance&&
			y > -tolerance && y < tolerance&&
			z > -tolerance && z < tolerance);
	}
	Vector	Normalize();
	float	NormalizeInPlace();
	inline float	DistTo(const Vector& vOther) const;
	inline float	DistToSqr(const Vector& vOther) const;
	float	Dot(const Vector& vOther) const;
	float	Length2D(void) const;
	float	Length2DSqr(void) const;
	Vector& operator=(const Vector& vOther);
	Vector	operator-(void) const;
	Vector	operator+(const Vector& v) const;
	Vector	operator-(const Vector& v) const;
	Vector	operator*(const Vector& v) const;
	Vector	operator/(const Vector& v) const;
	Vector	operator*(float fl) const;
	Vector	operator/(float fl) const;
	inline void Random(float minVal, float maxVal);
	// Base address...
	float* Base();
	float const* Base() const;

	bool operator!() { return !x && !y && !z; }

	Vector Vector::Normalized() const
	{
		Vector res = *this;
		float l = res.Length();
		if (l != 0.0f) {
			res /= l;
		}
		else {
			res.x = res.y = res.z = 0.0f;
		}
		return res;
	}

	Vector Direction()
	{
		return Vector(cos(y * M_PI / 180.0f) * cos(x * M_PI / 180.0f), sin(y * M_PI / 180.0f) * cos(x * M_PI / 180.0f), sin(-x * M_PI / 180.0f)).Normalized();
	}
	void VectorCrossProduct(const Vector& a, const Vector& b, Vector& result)
	{
		result.x = a.y * b.z - a.z * b.y;
		result.y = a.z * b.x - a.x * b.z;
		result.z = a.x * b.y - a.y * b.x;
	}
	Vector Cross(const Vector& vOther)
	{
		Vector res;
		VectorCrossProduct(*this, vOther, res);
		return res;
	}
};
inline void Vector::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
}
//===============================================
inline void Vector::Init(float ix, float iy, float iz)
{
	x = ix; y = iy; z = iz;
	CHECK_VALID(*this);
}
//===============================================
inline Vector::Vector(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
	CHECK_VALID(*this);
}
//===============================================
inline Vector::Vector(void) { }
//===============================================
inline void Vector::Zero()
{
	x = y = z = 0.0f;
}
//===============================================
inline void VectorClear(Vector& a)
{
	a.x = a.y = a.z = 0.0f;
}
//===============================================
inline Vector& Vector::operator=(const Vector& vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}
//===============================================
inline float& Vector::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline float Vector::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline bool Vector::operator==(const Vector& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y) && (src.z == z);
}
//===============================================
inline bool Vector::operator!=(const Vector& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y) || (src.z != z);
}
//===============================================
inline void VectorCopy(const Vector& src, Vector& dst)
{
	CHECK_VALID(src);
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}
//===============================================
inline  Vector& Vector::operator+=(const Vector& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x; y += v.y; z += v.z;
	return *this;
}
//===============================================
inline  Vector& Vector::operator-=(const Vector& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}
//===============================================
inline  Vector& Vector::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline  Vector& Vector::operator*=(const Vector& v)
{
	CHECK_VALID(v);
	x *= v.x;
	y *= v.y;
	z *= v.z;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline Vector& Vector::operator+=(float fl)
{
	x += fl;
	y += fl;
	z += fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline Vector& Vector::operator-=(float fl)
{
	x -= fl;
	y -= fl;
	z -= fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline  Vector& Vector::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline  Vector& Vector::operator/=(const Vector& v)
{
	CHECK_VALID(v);
	Assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
	x /= v.x;
	y /= v.y;
	z /= v.z;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline float Vector::Length(void) const
{
	CHECK_VALID(*this);

	float root = 0.0f;

	float sqsr = x * x + y * y + z * z;

	root = sqrt(sqsr);

	return root;
}
//===============================================
inline float Vector::Length2D(void) const
{
	CHECK_VALID(*this);

	float root = 0.0f;

	float sqst = x * x + y * y;

	root = sqrt(sqst);

	return root;
}
//===============================================
inline float Vector::Length2DSqr(void) const
{
	return (x * x + y * y);
}
//===============================================
inline Vector CrossProduct(const Vector& a, const Vector& b)
{
	return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
//===============================================
inline Vector operator*(float fl, const Vector& v)
{
	return v * fl;
}
float Vector::DistTo(const Vector& vOther) const
{
	Vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.Length();
}
float Vector::DistToSqr(const Vector& vOther) const
{
	Vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.LengthSqr();
}
//===============================================
inline Vector Vector::Normalize()
{
	Vector vector;
	float length = this->Length();

	if (length != 0)
	{
		vector.x = x / length;
		vector.y = y / length;
		vector.z = z / length;
	}
	else
	{
		vector.x = vector.y = 0.0f; vector.z = 1.0f;
	}

	return vector;
}
//===============================================
inline float Vector::NormalizeInPlace()
{
	Vector& v = *this;

	float iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

	v.x *= iradius;
	v.y *= iradius;
	v.z *= iradius;
	return 1;
}
//===============================================
inline float VectorNormalize(Vector& v)
{
	Assert(v.IsValid());
	float l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		// FIXME:
		// Just copying the existing implemenation; shouldn't res.z == 0?
		v.x = v.y = 0.0f; v.z = 1.0f;
	}
	return l;
}
//===============================================
inline float VectorNormalize(float* v)
{
	return VectorNormalize(*(reinterpret_cast<Vector*>(v)));
}
//===============================================
inline Vector Vector::operator+(const Vector& v) const
{
	Vector res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

//===============================================
inline Vector Vector::operator-(const Vector& v) const
{
	Vector res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}
//===============================================
inline Vector Vector::operator*(float fl) const
{
	Vector res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}
//===============================================
inline Vector Vector::operator*(const Vector& v) const
{
	Vector res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}
//===============================================
inline Vector Vector::operator/(float fl) const
{
	Vector res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}
//===============================================
inline Vector Vector::operator/(const Vector& v) const
{
	Vector res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}
inline float Vector::Dot(const Vector& vOther) const
{
	const Vector& a = *this;

	return(a.x * vOther.x + a.y * vOther.y + a.z * vOther.z);
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------

inline float VectorLength(const Vector& v)
{
	CHECK_VALID(v);
	return (float)FastSqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

//VECTOR SUBTRAC
inline void VectorSubtract(const Vector& a, const Vector& b, Vector& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

//VECTORADD
inline void VectorAdd(const Vector& a, const Vector& b, Vector& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* Vector::Base()
{
	return (float*)this;
}

inline float const* Vector::Base() const
{
	return (float const*)this;
}

inline void VectorMAInline(const float* start, float scale, const float* direction, float* dest)
{
	dest[0] = start[0] + direction[0] * scale;
	dest[1] = start[1] + direction[1] * scale;
	dest[2] = start[2] + direction[2] * scale;
}

inline void VectorMAInline(const Vector& start, float scale, const Vector& direction, Vector& dest)
{
	dest.x = start.x + direction.x * scale;
	dest.y = start.y + direction.y * scale;
	dest.z = start.z + direction.z * scale;
}

inline void VectorMA(const Vector& start, float scale, const Vector& direction, Vector& dest)
{
	VectorMAInline(start, scale, direction, dest);
}

inline void VectorMA(const float* start, float scale, const float* direction, float* dest)
{
	VectorMAInline(start, scale, direction, dest);
}

using vec_t = float;
class __declspec(align(16)) VectorAligned : public Vector
{
public:
	inline VectorAligned(void) {};
	inline VectorAligned(vec_t X, vec_t Y, vec_t Z)
	{
		Init(X, Y, Z);
	}

public:
	explicit VectorAligned(const Vector& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
	}

	VectorAligned& operator=(const Vector& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	VectorAligned& operator=(const VectorAligned& vOther)
	{
		_mm_store_ps(Base(), _mm_load_ps(vOther.Base()));
		return *this;
	}

	float w;
};



inline unsigned long& FloatBits(float& f)
{
	return *reinterpret_cast<unsigned long*>(&f);
}

inline bool IsFinite(float f)
{
	return ((FloatBits(f) & 0x7F800000) != 0x7F800000);
}


class Vector3 final
{
public:

	float x = 0, y = 0, z = 0;
	Vector3() = default;
	Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	Vector3 operator + (const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator - (const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator * (const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
	Vector3 operator / (const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }
	bool operator == (const Vector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
	bool operator != (const Vector3& rhs) const { return x != rhs.x || y != rhs.y || z != rhs.z; }
	Vector3& operator += (const Vector3& rhs) { return *this = *this + rhs; }
	Vector3& operator -= (const Vector3& rhs) { return *this = *this - rhs; }
	Vector3& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector3& operator /= (const float& rhs) { return *this = *this / rhs; }
	void Invert() { *this *= -1; }
	[[nodiscard]] float Length() const { return x * x + y * y + z * z; }
	[[nodiscard]] float SquaredLength() const { return std::sqrt(Length()); }
	[[nodiscard]] Vector3 Normalize() const { return *this * (1 / SquaredLength()); }
	[[nodiscard]] float Distance(const Vector3& rhs) const { return (*this - rhs).SquaredLength(); }
	[[nodiscard]] const char* ToString(const int d) const { static char buffer[128]; snprintf(buffer, 128, "[%.*f, %.*f, %.*f]", d, x, d, y, d, z); return buffer; }
	[[nodiscard]] bool Invalid() const { return x == 0 && y == 0 && z == 0; }
	static Vector3 zero() { return Vector3(); }
};

//=========================================================
// 2D Vector2D
//=========================================================

class Vector2
{
public:
	float x, y;

	Vector2()
	{
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2 operator -(const Vector2& v)
	{
		return Vector2(x - v.x, y - v.y);
	}

	void operator -=(const Vector2& v)
	{
		x -= v.x;
		y -= v.y;
	}

	Vector2 operator +(const Vector2& v)
	{
		return Vector2(x + v.x, y + v.y);
	}

	Vector2 operator +(const float& v)
	{
		return Vector2(x + v, y + v);
	}

	Vector2 operator -(const float& v)
	{
		return Vector2(x - v, y - v);
	}

	Vector2 operator +(const int& v)
	{
		return Vector2(x + v, y + v);
	}

	Vector2 operator -(const int& v)
	{
		return Vector2(x - v, y - v);
	}

	void operator +=(const Vector2& v)
	{
		x += v.x;
		y += v.y;
	}

	Vector2 operator *(const Vector2& v)
	{
		return Vector2(x * v.x, y * v.y);
	}

	Vector2 operator *(const float& a)
	{
		return Vector2(x * a, y * a);
	}

	Vector2 operator *=(const float& a)
	{
		return Vector2(x * a, y * a);
	}

	Vector2 operator /(const float& a)
	{
		if (x != 0.0f) {
			return Vector2(x / a, y / a);
		}
		else {
			return Vector2(x, y);
		}
	}

	void operator /=(const Vector2& v)
	{
		x /= v.x;
		y /= v.y;
	}

	void operator /=(const float& a)
	{
		x /= a;
		y /= a;
	}

	bool operator ==(const Vector2& v)
	{
		return (v.x == x) && (v.y == y);
	}

	float getAngle(Vector2* point)
	{
		if (!point || !this)
			return 0;

		auto dot = point->x * this->x + point->y * this->y;      // dot product between[x1, y1] and [x2, y2]
		auto det = point->x * this->y - point->y * this->x;    // determinant
		float angle = atan2(det, dot); // atan2(y, x) or atan2(sin, cos)
		return angle;
	}

	float getDistance(Vector2* point)
	{
		return hypot(this->x - point->x, this->y - point->y);
	}
};

class Vector2D
{
public:
	// Members
	float x, y;

	// Construction/destruction
	Vector2D(void);
	Vector2D(float X, float Y);
	Vector2D(const float* pFloat);

	// Initialization
	void Init(float ix = 0.0f, float iy = 0.0f);

	// Got any nasty NAN's?
	bool IsValid() const;

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	// Base address...
	float* Base();
	float const* Base() const;

	// Initialization methods
	void Random(float minVal, float maxVal);

	// equality
	bool operator==(const Vector2D& v) const;
	bool operator!=(const Vector2D& v) const;

	// arithmetic operations
	Vector2D& operator+=(const Vector2D& v);
	Vector2D& operator-=(const Vector2D& v);
	Vector2D& operator*=(const Vector2D& v);
	Vector2D& operator*=(float s);
	Vector2D& operator/=(const Vector2D& v);
	Vector2D& operator/=(float s);

	// negate the Vector2D components
	void	Negate();

	// Get the Vector2D's magnitude.
	float	Length() const;

	// Get the Vector2D's magnitude squared.
	float	LengthSqr(void) const;

	// return true if this vector is (0,0) within tolerance
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance&&
			y > -tolerance && y < tolerance);
	}

	float	Normalize();

	// Normalize in place and return the old length.
	float	NormalizeInPlace();

	// Compare length.
	bool	IsLengthGreaterThan(float val) const;
	bool	IsLengthLessThan(float val) const;

	// Get the distance from this Vector2D to the other one.
	float	DistTo(const Vector2D& vOther) const;

	// Get the distance from this Vector2D to the other one squared.
	float	DistToSqr(const Vector2D& vOther) const;

	// Copy
	void	CopyToArray(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual Vector2D equation (because it's done per-component
	// rather than per-Vector2D).
	void	MulAdd(const Vector2D& a, const Vector2D& b, float scalar);

	// Dot product.
	float	Dot(const Vector2D& vOther) const;

	// assignment
	Vector2D& operator=(const Vector2D& vOther);

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// copy constructors
	Vector2D(const Vector2D& vOther);

	// arithmetic operations
	Vector2D	operator-(void) const;

	Vector2D	operator+(const Vector2D& v) const;
	Vector2D	operator-(const Vector2D& v) const;
	Vector2D	operator*(const Vector2D& v) const;
	Vector2D	operator/(const Vector2D& v) const;
	Vector2D	operator*(float fl) const;
	Vector2D	operator/(float fl) const;

	// Cross product between two vectors.
	Vector2D	Cross(const Vector2D& vOther) const;

	// Returns a Vector2D with the min or max in X, Y, and Z.
	Vector2D	Min(const Vector2D& vOther) const;
	Vector2D	Max(const Vector2D& vOther) const;

#else

private:
	// No copy constructors allowed if we're in optimal mode
	Vector2D(const Vector2D& vOther);
#endif
};

//-----------------------------------------------------------------------------

const Vector2D vec2_origin(0, 0);
//const Vector2D vec2_invalid(3.40282347E+38F, 3.40282347E+38F);

//-----------------------------------------------------------------------------
// Vector2D related operations
//-----------------------------------------------------------------------------

// Vector2D clear
void Vector2DClear(Vector2D& a);

// Copy
void Vector2DCopy(const Vector2D& src, Vector2D& dst);

// Vector2D arithmetic
void Vector2DAdd(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DSubtract(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DMultiply(const Vector2D& a, float b, Vector2D& result);
void Vector2DMultiply(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DDivide(const Vector2D& a, float b, Vector2D& result);
void Vector2DDivide(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DMA(const Vector2D& start, float s, const Vector2D& dir, Vector2D& result);

// Store the min or max of each of x, y, and z into the result.
void Vector2DMin(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DMax(const Vector2D& a, const Vector2D& b, Vector2D& result);

#define Vector2DExpand( v ) (v).x, (v).y

// Normalization
float Vector2DNormalize(Vector2D& v);

// Length
float Vector2DLength(const Vector2D& v);

// Dot Product
float DotProduct2D(const Vector2D& a, const Vector2D& b);

// Linearly interpolate between two vectors
void Vector2DLerp(const Vector2D& src1, const Vector2D& src2, float t, Vector2D& dest);


//-----------------------------------------------------------------------------
//
// Inlined Vector2D methods
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------

inline Vector2D::Vector2D(void)
{
#ifdef _DEBUG
	// Initialize to NAN to catch errors
	//x = y = float_NAN;
#endif
}

inline Vector2D::Vector2D(float X, float Y)
{
	x = X; y = Y;
	Assert(IsValid());
}

inline Vector2D::Vector2D(const float* pFloat)
{
	Assert(pFloat);
	x = pFloat[0]; y = pFloat[1];
	Assert(IsValid());
}


//-----------------------------------------------------------------------------
// copy constructor
//-----------------------------------------------------------------------------

inline Vector2D::Vector2D(const Vector2D& vOther)
{
	Assert(vOther.IsValid());
	x = vOther.x; y = vOther.y;
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

inline void Vector2D::Init(float ix, float iy)
{
	x = ix; y = iy;
	Assert(IsValid());
}

inline void Vector2D::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
}

inline void Vector2DClear(Vector2D& a)
{
	a.x = a.y = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

inline Vector2D& Vector2D::operator=(const Vector2D& vOther)
{
	Assert(vOther.IsValid());
	x = vOther.x; y = vOther.y;
	return *this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

inline float& Vector2D::operator[](int i)
{
	Assert((i >= 0) && (i < 2));
	return ((float*)this)[i];
}

inline float Vector2D::operator[](int i) const
{
	Assert((i >= 0) && (i < 2));
	return ((float*)this)[i];
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------

inline float* Vector2D::Base()
{
	return (float*)this;
}

inline float const* Vector2D::Base() const
{
	return (float const*)this;
}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

//inline bool Vector2D::IsValid() const
//{
//	return IsFinite(x) && IsFinite(y);
//}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

inline bool Vector2D::operator==(const Vector2D& src) const
{
	Assert(src.IsValid() && IsValid());
	return (src.x == x) && (src.y == y);
}

inline bool Vector2D::operator!=(const Vector2D& src) const
{
	Assert(src.IsValid() && IsValid());
	return (src.x != x) || (src.y != y);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

inline void Vector2DCopy(const Vector2D& src, Vector2D& dst)
{
	Assert(src.IsValid());
	dst.x = src.x;
	dst.y = src.y;
}

inline void	Vector2D::CopyToArray(float* rgfl) const
{
	Assert(IsValid());
	Assert(rgfl);
	rgfl[0] = x; rgfl[1] = y;
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------

inline void Vector2D::Negate()
{
	Assert(IsValid());
	x = -x; y = -y;
}

inline Vector2D& Vector2D::operator+=(const Vector2D& v)
{
	Assert(IsValid() && v.IsValid());
	x += v.x; y += v.y;
	return *this;
}

inline Vector2D& Vector2D::operator-=(const Vector2D& v)
{
	Assert(IsValid() && v.IsValid());
	x -= v.x; y -= v.y;
	return *this;
}

inline Vector2D& Vector2D::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	Assert(IsValid());
	return *this;
}

inline Vector2D& Vector2D::operator*=(const Vector2D& v)
{
	x *= v.x;
	y *= v.y;
	Assert(IsValid());
	return *this;
}

inline Vector2D& Vector2D::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	Assert(IsValid());
	return *this;
}

inline Vector2D& Vector2D::operator/=(const Vector2D& v)
{
	Assert(v.x != 0.0f && v.y != 0.0f);
	x /= v.x;
	y /= v.y;
	Assert(IsValid());
	return *this;
}

inline void Vector2DAdd(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid() && b.IsValid());
	c.x = a.x + b.x;
	c.y = a.y + b.y;
}

inline void Vector2DSubtract(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid() && b.IsValid());
	c.x = a.x - b.x;
	c.y = a.y - b.y;
}

inline void Vector2DMultiply(const Vector2D& a, float b, Vector2D& c)
{
	Assert(a.IsValid() && IsFinite(b));
	c.x = a.x * b;
	c.y = a.y * b;
}

inline void Vector2DMultiply(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid() && b.IsValid());
	c.x = a.x * b.x;
	c.y = a.y * b.y;
}


inline void Vector2DDivide(const Vector2D& a, float b, Vector2D& c)
{
	Assert(a.IsValid());
	Assert(b != 0.0f);
	float oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
}

inline void Vector2DDivide(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid());
	Assert((b.x != 0.0f) && (b.y != 0.0f));
	c.x = a.x / b.x;
	c.y = a.y / b.y;
}

inline void Vector2DMA(const Vector2D& start, float s, const Vector2D& dir, Vector2D& result)
{
	Assert(start.IsValid() && IsFinite(s) && dir.IsValid());
	result.x = start.x + s * dir.x;
	result.y = start.y + s * dir.y;
}

// FIXME: Remove
// For backwards compatability
inline void	Vector2D::MulAdd(const Vector2D& a, const Vector2D& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
}

inline void Vector2DLerp(const Vector2D& src1, const Vector2D& src2, float t, Vector2D& dest)
{
	dest[0] = src1[0] + (src2[0] - src1[0]) * t;
	dest[1] = src1[1] + (src2[1] - src1[1]) * t;
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------
inline float DotProduct2D(const Vector2D& a, const Vector2D& b)
{
	Assert(a.IsValid() && b.IsValid());
	return(a.x * b.x + a.y * b.y);
}

// for backwards compatability
inline float Vector2D::Dot(const Vector2D& vOther) const
{
	return DotProduct2D(*this, vOther);
}


//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline float Vector2DLength(const Vector2D& v)
{
	Assert(v.IsValid());
	return (float)FastSqrt(v.x * v.x + v.y * v.y);
}

inline float Vector2D::LengthSqr(void) const
{
	Assert(IsValid());
	return (x * x + y * y);
}

inline float Vector2D::NormalizeInPlace()
{
	return Vector2DNormalize(*this);
}

inline bool Vector2D::IsLengthGreaterThan(float val) const
{
	return LengthSqr() > val * val;
}

inline bool Vector2D::IsLengthLessThan(float val) const
{
	return LengthSqr() < val * val;
}

inline float Vector2D::Length(void) const
{
	return Vector2DLength(*this);
}


inline void Vector2DMin(const Vector2D& a, const Vector2D& b, Vector2D& result)
{
	result.x = (a.x < b.x) ? a.x : b.x;
	result.y = (a.y < b.y) ? a.y : b.y;
}


inline void Vector2DMax(const Vector2D& a, const Vector2D& b, Vector2D& result)
{
	result.x = (a.x > b.x) ? a.x : b.x;
	result.y = (a.y > b.y) ? a.y : b.y;
}


//-----------------------------------------------------------------------------
// Normalization
//-----------------------------------------------------------------------------
inline float Vector2DNormalize(Vector2D& v)
{
	Assert(v.IsValid());
	float l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		v.x = v.y = 0.0f;
	}
	return l;
}


//-----------------------------------------------------------------------------
// Get the distance from this Vector2D to the other one
//-----------------------------------------------------------------------------
inline float Vector2D::DistTo(const Vector2D& vOther) const
{
	Vector2D delta;
	Vector2DSubtract(*this, vOther, delta);
	return delta.Length();
}

inline float Vector2D::DistToSqr(const Vector2D& vOther) const
{
	Vector2D delta;
	Vector2DSubtract(*this, vOther, delta);
	return delta.LengthSqr();
}


//-----------------------------------------------------------------------------
// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
//-----------------------------------------------------------------------------
inline void ComputeClosestPoint2D(const Vector2D& vecStart, float flMaxDist, const Vector2D& vecTarget, Vector2D* pResult)
{
	Vector2D vecDelta;
	Vector2DSubtract(vecTarget, vecStart, vecDelta);
	float flDistSqr = vecDelta.LengthSqr();
	if (flDistSqr <= flMaxDist * flMaxDist)
	{
		*pResult = vecTarget;
	}
	else
	{
		vecDelta /= FastSqrt(flDistSqr);
		Vector2DMA(vecStart, flMaxDist, vecDelta, *pResult);
	}
}



//-----------------------------------------------------------------------------
//
// Slow methods
//
//-----------------------------------------------------------------------------

#ifndef VECTOR_NO_SLOW_OPERATIONS
#endif
//-----------------------------------------------------------------------------
// Returns a Vector2D with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------

inline Vector2D Vector2D::Min(const Vector2D& vOther) const
{
	return Vector2D(x < vOther.x ? x : vOther.x,
		y < vOther.y ? y : vOther.y);
}

inline Vector2D Vector2D::Max(const Vector2D& vOther) const
{
	return Vector2D(x > vOther.x ? x : vOther.x,
		y > vOther.y ? y : vOther.y);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

inline Vector2D Vector2D::operator-(void) const
{
	return Vector2D(-x, -y);
}

inline Vector2D Vector2D::operator+(const Vector2D& v) const
{
	Vector2D res;
	Vector2DAdd(*this, v, res);
	return res;
}

inline Vector2D Vector2D::operator-(const Vector2D& v) const
{
	Vector2D res;
	Vector2DSubtract(*this, v, res);
	return res;
}

inline Vector2D Vector2D::operator*(float fl) const
{
	Vector2D res;
	Vector2DMultiply(*this, fl, res);
	return res;
}

inline Vector2D Vector2D::operator*(const Vector2D& v) const
{
	Vector2D res;
	Vector2DMultiply(*this, v, res);
	return res;
}

inline Vector2D Vector2D::operator/(float fl) const
{
	Vector2D res;
	Vector2DDivide(*this, fl, res);
	return res;
}

inline Vector2D Vector2D::operator/(const Vector2D& v) const
{
	Vector2D res;
	Vector2DDivide(*this, v, res);
	return res;
}

inline Vector2D operator*(float fl, const Vector2D& v)
{
	return v * fl;
}

class QAngleByValue;
class QAngle
{
public:
	// Members
	float x, y, z;

	// Construction/destruction
	QAngle(void);
	QAngle(float X, float Y, float Z);
	//      QAngle(RadianEuler const &angles);      // evil auto type promotion!!!

	// Allow pass-by-value
	operator QAngleByValue& () { return *((QAngleByValue*)(this)); }
	operator const QAngleByValue& () const { return *((const QAngleByValue*)(this)); }

	// Initialization
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	void Random(float minVal, float maxVal);

	// Got any nasty NAN's?
	bool IsValid() const;
	void Invalidate();

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	// Base address...
	float* Base();
	float const* Base() const;

	// equality
	bool operator==(const QAngle& v) const;
	bool operator!=(const QAngle& v) const;

	// arithmetic operations
	QAngle& operator+=(const QAngle& v);
	QAngle& operator-=(const QAngle& v);
	QAngle& operator*=(float s);
	QAngle& operator/=(float s);

	// Get the vector's magnitude.
	float   Length() const;
	float   LengthSqr() const;

	// negate the QAngle components
	//void  Negate();

	// No assignment operators either...
	QAngle& operator=(const QAngle& src);

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// copy constructors

	// arithmetic operations
	QAngle  operator-(void) const;

	QAngle  operator+(const QAngle& v) const;
	QAngle  operator-(const QAngle& v) const;
	QAngle  operator*(float fl) const;
	QAngle  operator/(float fl) const;
#else

private:
	// No copy constructors allowed if we're in optimal mode
	QAngle(const QAngle& vOther);

#endif
};

//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------
inline QAngle::QAngle(void)
{
#ifdef _DEBUG
#ifdef VECTOR_PARANOIA
	// Initialize to NAN to catch errors
	x = y = z = VEC_T_NAN;
#endif
#endif
}

inline QAngle::QAngle(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
	CHECK_VALID(*this);
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------
inline void QAngle::Init(float ix, float iy, float iz)
{
	x = ix; y = iy; z = iz;
	CHECK_VALID(*this);
}

inline void QAngle::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	CHECK_VALID(*this);
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator=(const QAngle& vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------
inline bool QAngle::operator==(const QAngle& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y) && (src.z == z);
}

inline bool QAngle::operator!=(const QAngle& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y) || (src.z != z);
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator+=(const QAngle& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x; y += v.y; z += v.z;
	return *this;
}

inline QAngle& QAngle::operator-=(const QAngle& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}

inline QAngle& QAngle::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID(*this);
	return *this;
}

inline QAngle& QAngle::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID(*this);
	return *this;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* QAngle::Base()
{
	return (float*)this;
}

inline float const* QAngle::Base() const
{
	return (float const*)this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline float& QAngle::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

inline float QAngle::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline float QAngle::Length() const
{
	CHECK_VALID(*this);
	return (float)FastSqrt(LengthSqr());
}


inline float QAngle::LengthSqr() const
{
	CHECK_VALID(*this);
	return x * x + y * y + z * z;
}


//-----------------------------------------------------------------------------
// arithmetic operations (SLOW!!)
//-----------------------------------------------------------------------------
#ifndef VECTOR_NO_SLOW_OPERATIONS

inline QAngle QAngle::operator-(void) const
{
	return QAngle(-x, -y, -z);
}

inline QAngle QAngle::operator+(const QAngle& v) const
{
	QAngle res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

inline QAngle QAngle::operator-(const QAngle& v) const
{
	QAngle res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}

inline QAngle QAngle::operator*(float fl) const
{
	QAngle res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}

inline QAngle QAngle::operator/(float fl) const
{
	QAngle res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}

inline QAngle operator*(float fl, const QAngle& v)
{
	return v * fl;
}

#endif // VECTOR_NO_SLOW_OPERATIONS


//QANGLE SUBTRAC
inline void QAngleSubtract(const QAngle& a, const QAngle& b, QAngle& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

//QANGLEADD
inline void QAngleAdd(const QAngle& a, const QAngle& b, QAngle& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}



#define CHECK_VALID(_v) 0
#define Assert(_exp) ((void)0)


//
//class Vector3
//{
//public:
//
//	float X, Y, Z;
//
//	Vector3() {};
//	Vector3(float X, float Y, float Z) : X{ X }, Y{ Y }, Z{ Z } {}
//	Vector3(float* xyz) { X = xyz[0]; Y = xyz[1]; Z = xyz[2]; }
//	Vector3(const Vector3& v) { X = v.X; Y = v.Y; Z = v.Z; }
//	Vector3(Vector3&& v) : X(0), Y(0), Z(0)
//	{
//		X = v.X;
//		Y = v.Y;
//		Z = v.Z;
//
//		v.X = 0;
//		v.Y = 0;
//		v.Z = 0;
//	}
//
//	~Vector3() {};
//
//	inline void init(float X, float Y, float Z)
//	{
//		this->X = X; this->Y = Y; this->Z = Z;
//	}
//
//	inline float* base()
//	{
//		return (float*)this;
//	}
//
//	inline float const* base() const
//	{
//		return (float const*)this;
//	}
//
//	inline float operator[](int i) const
//	{
//		return ((float*)this)[i];
//	}
//
//	inline float& operator[](int i)
//	{
//		return ((float*)this)[i];
//	}
//
//	//inline float length()
//	//{
//	//	float root = 0.0f;
//
//	//	float sqsr = (this->X * this->X) + (this->Y * this->Y) + (this->Z * this->Z);
//
//	//	_asm
//	//	{
//	//		sqrtss xmm0, sqsr
//	//		movss root, xmm0
//	//	}
//
//	//	return root;
//	//}
//
//	/*inline Vector3 normalize()
//	{
//		Vector3 vekt;
//		float len = this->length();
//
//		if (len != 0)
//		{
//			vekt.X = this->X / len;
//			vekt.Y = this->Y / len;
//			vekt.Z = this->Z / len;
//		}
//		else
//		{
//			vekt.X = vekt.Y = 0.0f;
//			vekt.Z = 1.0f;
//		}
//
//		return vekt;
//	}*/
//
//	/*inline float normalizeInPlace()
//	{
//		Vector3& vekt = *this;
//
//		float iradius = 1.f / (this->length() + 1.192092896e-07F);
//
//		vekt.X *= iradius;
//		vekt.Y *= iradius;
//		vekt.Z *= iradius;
//	}*/
//
//	/*inline float length2d()
//	{
//		float root = 0.0f;
//		float sqs = (this->X * this->X) + (this->Y * this->Y);
//
//		_asm
//		{
//			sqrtss xmm0, sqs
//			movss root, xmm0
//		}
//		return root;
//	}*/
//
//	inline float lengthSqr()
//	{
//		return (pow(this->X, 2) + pow(this->Y, 2) + pow(this->Z, 2));
//	}
//
//	inline void clearVekt()
//	{
//		this->X = this->Y = this->Z = 0.0f;
//	}
//
//	inline bool Vector3::operator==(const Vector3& src) const
//	{
//		CHECK_VALID(src);
//		CHECK_VALID(*this);
//		return (src.X == X) && (src.Y == Y) && (src.Z == Z);
//	}
//
//	inline Vector3 operator+(const Vector3& v) const
//	{
//		return Vector3(this->X + v.X, this->Y + v.Y, this->Z + v.Z);
//	}
//
//	inline Vector3 operator-(const Vector3& v) const
//	{
//		return Vector3(this->X - v.X, this->Y - v.Y, this->Z - v.Z);
//	}
//
//	inline Vector3 operator*(const Vector3& v) const
//	{
//		return Vector3(this->X * v.X, this->Y * v.Y, this->Z * v.Z);
//	}
//
//	inline Vector3 operator*(float f) const
//	{
//		return Vector3(this->X * f, this->Y * f, this->Z * f);
//	}
//
//	inline Vector3 operator/(const Vector3& v) const
//	{
//		return Vector3(this->X / v.X, this->Y / v.Y, this->Z / v.Z);
//	}
//
//	inline Vector3 operator/(float f) const
//	{
//		return Vector3(this->X / f, this->Y / f, this->Z / f);
//	}
//
//	inline Vector3& operator+=(const Vector3& v)
//	{
//		this->X += v.X;
//		this->Y += v.Y;
//		this->Z += v.Z;
//
//		return *this;
//	}
//
//	inline Vector3& operator-=(const Vector3& v)
//	{
//		this->X -= v.X;
//		this->Y -= v.Y;
//		this->Z -= v.Z;
//
//		return *this;
//	}
//
//	inline Vector3& operator*=(const Vector3& v)
//	{
//		this->X *= v.X;
//		this->Y *= v.Y;
//		this->Z *= v.Z;
//
//		return *this;
//	}
//
//	inline Vector3& operator/=(const Vector3& v)
//	{
//		this->X /= v.X;
//		this->Y /= v.Y;
//		this->Z /= v.Z;
//
//		return *this;
//	}
//
//	inline Vector3& operator*=(float f)
//	{
//		this->X *= f;
//		this->Y *= f;
//		this->Z *= f;
//
//		return *this;
//	}
//
//	inline Vector3& operator/=(float f)
//	{
//		this->X /= f;
//		this->Y /= f;
//		this->Z /= f;
//
//		return *this;
//	}
//
//	inline bool operator==(const Vector3& src)
//	{
//		return (src.X == X) && (src.Y == Y) && (src.Z == Z);
//	}
//
//	inline bool operator!=(const Vector3& src)
//	{
//		return (src.X != X) || (src.Y != Y) || (src.Z != Z);
//	}
//
//	inline bool operator!()
//	{
//		return !X && !Y && !Z;
//	}
//
//	inline Vector3& operator=(Vector3&& v)
//	{
//		if (this != &v)
//		{
//			X = 0;
//			Y = 0;
//			Z = 0;
//
//			X = v.X;
//			Y = v.Y;
//			Z = v.Z;
//
//			v.X = 0;
//			v.Y = 0;
//			v.Z = 0;
//		}
//
//		return *this;
//	}
//
//	inline Vector3& operator=(const Vector3& v)
//	{
//		if (this != &v)
//		{
//			X = v.X;
//			Y = v.Y;
//			Z = v.Z;
//		}
//
//		return *this;
//	}
//};
//
//inline Vector3 operator*(float fl, const Vector3& v) { return v * fl; }
//
//class __declspec(align(16)) Vector3Aligned : public Vector3
//{
//public:
//
//	Vector3Aligned() {}
//	Vector3Aligned(float X, float Y, float Z)
//	{
//		this->X = X;
//		this->Y = Y;
//		this->Z = Z;
//	}
//
//	explicit Vector3Aligned(const Vector3& v)
//	{
//		this->X = v.X;
//		this->Y = v.Y;
//		this->Z = v.Z;
//	}
//
//	inline Vector3Aligned& operator=(const Vector3& v)
//	{
//		this->X = v.X;
//		this->Y = v.Y;
//		this->Z = v.Z;
//
//		return *this;
//	}
//
//	inline Vector3Aligned& operator=(const Vector3Aligned& v)
//	{
//		_mm_store_ps(this->base(), _mm_load_ps(v.base()));
//
//		return *this;
//	}
//
//	float w;
//};
//
//inline void VectorMA(const Vector3& start, float scale, const Vector3& direction, Vector3& dest)
//{
//	CHECK_VALID(start);
//	CHECK_VALID(direction);
//
//	dest.X = start.X + scale * direction.X;
//	dest.Y = start.Y + scale * direction.Y;
//	dest.Z = start.Z + scale * direction.Z;
//}
//
//typedef unsigned __int32		uint32;
//
//inline uint32 const FloatBits(const float& f)
//{
//	union Convertor_t
//	{
//		float f;
//		uint32 ul;
//	}tmp;
//	tmp.f = f;
//	return tmp.ul;
//}
//
//inline bool IsFinite(const float& f)
//{
//#if _X360
//	return f == f && fabs(f) <= FLT_//MAX;
//#else
//	return ((FloatBits(f) & 0x7F800000) != 0x7F800000);
//#endif
//}
//
//inline void VectorMultiply(const Vector3& a, float b, Vector3& c)
//{
//	CHECK_VALID(a);
//	Assert(IsFinite(b));
//	c.X = a.X * b;
//	c.Y = a.Y * b;
//	c.Z = a.Z * b;
//}
//
//inline void CrossProduct(const Vector3& a, const Vector3& b, Vector3& result)
//{
//	CHECK_VALID(a);
//	CHECK_VALID(b);
//	Assert(&a != &result);
//	Assert(&b != &result);
//	result.X = a.Y * b.Z - a.Z * b.Y;
//	result.Y = a.Z * b.X - a.X * b.Z;
//	result.Z = a.X * b.Y - a.Y * b.X;
//}
//
//inline void VectorAdd(const Vector3& a, const Vector3& b, Vector3& c)
//{
//	CHECK_VALID(a);
//	CHECK_VALID(b);
//	c.X = a.X + b.X;
//	c.Y = a.Y + b.Y;
//	c.Z = a.Z + b.Z;
//}
//
//inline void VectorSubtract(const Vector3& a, const Vector3& b, Vector3& c)
//{
//	CHECK_VALID(a);
//	CHECK_VALID(b);
//	c.X = a.X - b.X;
//	c.Y = a.Y - b.Y;
//	c.Z = a.Z - b.Z;
//}
//
////inline float VectorNormalize(Vector3& v)
////{
////	float l = v.length();
////	if (l != 0.0f)
////	{
////		v /= l;
////	}
////	else
////	{
////		v.X = v.Y = v.Z = 0.0f;
////	}
////	return l;
////}