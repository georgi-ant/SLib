/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_MATH_PLANE
#define CHECKHEADER_SLIB_MATH_PLANE

#include "definition.h"

#include "vector3.h"
#include "line3.h"
#include "matrix4.h"

/*
	ax + by + cz + d = 0
 */

namespace slib
{

	template <class T>
	class SLIB_EXPORT PlaneT
	{
	public:
		T a;
		T b;
		T c;
		T d;

	public:
		SLIB_INLINE PlaneT() noexcept = default;

		SLIB_INLINE constexpr PlaneT(const PlaneT<T>& other)
		 : a(other.a), b(other.b), c(other.c), d(other.d)
		 {}

		template <class O>
		SLIB_INLINE constexpr PlaneT(const PlaneT<O>& other)
		 : a((T)(other.a)), b((T)(other.b)), c((T)(other.c)), d((T)(other.d))
		 {}

		SLIB_INLINE constexpr PlaneT(T _a, T _b, T _c, T _d)
		 : a(_a), b(_b), c(_c), d(_d)
		 {}

		PlaneT(const Vector3T<T>& point, const Vector3T<T>& normal) noexcept;

	public:
		Vector3T<T> getNormal() const noexcept;

		Vector3T<T> projectOriginOnNormalized() const noexcept;

		Vector3T<T> projectOrigin() const noexcept;

		T getDistanceFromPointOnNormalized(const Vector3T<T>& pos) const noexcept;

		T getDistanceFromPoint(const Vector3T<T>& pos) const noexcept;

		Vector3T<T> projectPointOnNormalized(const Vector3T<T>& pos) const noexcept;

		Vector3T<T> projectPoint(const Vector3T<T>& pos) const noexcept;

		void setFromPointAndNormal(const Vector3T<T>& point, const Vector3T<T>& normal) noexcept;

		void normalize() noexcept;

		void transform(const Matrix4T<T>& mat) noexcept;

		// return sl_true when the plane intersects to the line segment
		sl_bool intersectLine(
			const Line3T<T>& line,
			Vector3T<T>* outIntersectPoint = sl_null,
			sl_bool* pFlagParallel = sl_null,
			sl_bool* pFlagExtendPoint1 = sl_null,
			sl_bool* pFlagExtendPoint2 = sl_null) const noexcept;

		sl_bool intersectPlane(const PlaneT<T>& plane, Line3T<T>* outIntersectLine = sl_null, sl_bool* pFlagParallel = sl_null) const noexcept;

	public:
		PlaneT<T>& operator=(const PlaneT<T>& other) noexcept = default;

		template <class O>
		PlaneT<T>& operator=(const PlaneT<O>& other) noexcept;
	
	};
	
	extern template class PlaneT<float>;
	extern template class PlaneT<double>;
	typedef PlaneT<sl_real> Plane;
	typedef PlaneT<float> Planef;
	typedef PlaneT<double> Planelf;

}

#include "detail/plane.inc"

#endif
