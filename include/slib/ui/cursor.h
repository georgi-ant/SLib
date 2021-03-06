/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_UI_CURSOR
#define CHECKHEADER_SLIB_UI_CURSOR

#include "definition.h"

#include "../core/object.h"

namespace slib
{

	class SLIB_EXPORT Cursor : public Object
	{
		SLIB_DECLARE_OBJECT
		
	public:
		Cursor();

		~Cursor();

	public:
		static Ref<Cursor> getArrow();
		
		static Ref<Cursor> getIBeam();
		
		static Ref<Cursor> getCross();
		
		static Ref<Cursor> getHand();
		
		static Ref<Cursor> getResizeLeftRight();
		
		static Ref<Cursor> getResizeUpDown();
		
	public:
		static void setCurrent(const Ref<Cursor>& cursor);
		
		static Ref<Cursor> getCurrent();
		
	public:
		static void show();
		
		static void hide();
		
	};

}

#endif
