/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_CORE_DETAIL_SAFE_STATIC
#define CHECKHEADER_SLIB_CORE_DETAIL_SAFE_STATIC

#include "../safe_static.h"

namespace slib
{
	
	template <class T>
	class _SafeStaticDestructor
	{
	public:
		T* object;
		volatile sl_bool flagFreed;

	public:
		SLIB_INLINE _SafeStaticDestructor(T* p)
		: object(p), flagFreed(sl_false)
		{
		}

		~_SafeStaticDestructor()
		{
			flagFreed = sl_true;
			object->~T();
		}

	};

}

#endif

