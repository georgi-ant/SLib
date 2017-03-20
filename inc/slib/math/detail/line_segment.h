/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_MATH_DETAIL_LINE_SEGMENT
#define CHECKHEADER_SLIB_MATH_DETAIL_LINE_SEGMENT

#include "../line_segment.h"

namespace slib
{
	
	template <class T>
	template <class O>
	SLIB_INLINE LineSegmentT<T>::LineSegmentT(const LineSegmentT<O>& other)
	: point1(other.point1), point2(other.point2)
	{
	}
	
	template <class T>
	template <class O>
	SLIB_INLINE LineSegmentT<T>& LineSegmentT<T>::operator=(const LineSegmentT<O>& other)
	{
		point1 = other.point1;
		point2 = other.point2;
		return *this;
	}

}

#endif
