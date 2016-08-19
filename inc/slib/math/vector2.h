#ifndef CHECKHEADER_SLIB_MATH_VECTOR2
#define CHECKHEADER_SLIB_MATH_VECTOR2

#include "definition.h"

SLIB_MATH_NAMESPACE_BEGIN

template <class T, class FT = T>
class SLIB_EXPORT Vector2T
{
public:
	T x;
	T y;

public:
	Vector2T() = default;
	
	Vector2T(const Vector2T<T, FT>& other) = default;

	template <class O, class FO>
	Vector2T(const Vector2T<O, FO>& other);

	Vector2T(T x, T y);
	
public:
	static const Vector2T<T, FT>& zero();
	
	T dot(const Vector2T<T, FT>& other) const;
	
	T cross(const Vector2T<T, FT>& other) const;
	
	T getLength2p() const;
	
	FT getLength() const;
	
	T getLength2p(const Vector2T<T, FT>& other) const;
	
	FT getLength(const Vector2T<T, FT>& other) const;
	
	void normalize();
	
	Vector2T<T, FT> getNormalized();
	
	FT getCosBetween(const Vector2T<T, FT>& other) const;
	
	FT getAbsAngleBetween(const Vector2T<T, FT>& other) const;
	
	FT getAngleBetween(const Vector2T<T, FT>& other) const;
	
	sl_bool equals(const Vector2T<T, FT>& other) const;
	
	sl_bool isAlmostEqual(const Vector2T<T, FT>& other) const;

public:
	Vector2T<T, FT>& operator=(const Vector2T<T, FT>& other) = default;
	
	template <class O, class FO>
	Vector2T<T, FT>& operator=(const Vector2T<O, FO>& other);
	
	Vector2T<T, FT> operator+(const Vector2T<T, FT>& other) const;
	
	Vector2T<T, FT>& operator+=(const Vector2T<T, FT>& other);
	
	Vector2T<T, FT> operator-(const Vector2T<T, FT>& other) const;
	
	Vector2T<T, FT>& operator-=(const Vector2T<T, FT>& other);
	
	Vector2T<T, FT> operator*(T f) const;
	
	Vector2T<T, FT>& operator*=(T f);
	
	Vector2T<T, FT> operator*(const Vector2T<T, FT>& other) const;
	
	Vector2T<T, FT>& operator*=(const Vector2T<T, FT>& other);
	
	Vector2T<T, FT> operator/(T f) const;
	
	Vector2T<T, FT>& operator/=(T f);
	
	Vector2T<T, FT> operator/(const Vector2T<T, FT>& other) const;
	
	Vector2T<T, FT>& operator/(const Vector2T<T, FT>& other);
	
	Vector2T<T, FT> operator-() const;
	
	sl_bool operator==(const Vector2T<T, FT>& other) const;
	
	sl_bool operator!=(const Vector2T<T, FT>& other) const;
	
private:
	static T _zero[2];
	
};


SLIB_DECLARE_GEOMETRY_TYPE_EX(Vector2)

template <class T, class FT>
Vector2T<T, FT> operator*(T f, const Vector2T<T, FT>& v);

template <class T, class FT>
Vector2T<T, FT> operator/(T f, const Vector2T<T, FT>& v);


SLIB_MATH_NAMESPACE_END


SLIB_MATH_NAMESPACE_BEGIN

template <class T, class FT>
template <class O, class FO>
SLIB_INLINE Vector2T<T, FT>::Vector2T(const Vector2T<O, FO>& other) : x((T)(other.x)), y((T)(other.y))
{
}

template <class T, class FT>
SLIB_INLINE Vector2T<T, FT>::Vector2T(T _x, T _y) : x(_x), y(_y)
{
}

template <class T, class FT>
SLIB_INLINE const Vector2T<T, FT>& Vector2T<T, FT>::zero()
{
	return *((Vector2T<T, FT>*)((void*)(_zero)));
}

template <class T, class FT>
template <class O, class FO>
SLIB_INLINE Vector2T<T, FT>& Vector2T<T, FT>::operator=(const Vector2T<O, FO>& other)
{
	x = (T)(other.x);
	y = (T)(other.y);
	return *this;
}

template <class T, class FT>
Vector2T<T, FT> operator*(T f, const Vector2T<T, FT>& v)
{
	return {f * v.x, f * v.y};
}

template <class T, class FT>
Vector2T<T, FT> operator/(T f, const Vector2T<T, FT>& v)
{
	return {f / v.x, f / v.y};
}

SLIB_MATH_NAMESPACE_END

#endif