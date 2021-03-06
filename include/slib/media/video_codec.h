/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_MEDIA_VIDEO_CODEC
#define CHECKHEADER_SLIB_MEDIA_VIDEO_CODEC

#include "definition.h"

#include "video_frame.h"

#include "../core/object.h"

namespace slib
{
	class SLIB_EXPORT VideoEncoder : public Object
	{
		SLIB_DECLARE_OBJECT
		
	protected:
		VideoEncoder();
		
		~VideoEncoder();
		
	public:
		virtual Memory encode(const VideoFrame& input) = 0;
		
	public:
		sl_uint32 getBitrate();
		
		virtual void setBitrate(sl_uint32 bitrate);
		
	protected:
		sl_uint32 m_nWidth;
		sl_uint32 m_nHeight;
		sl_uint32 m_nKeyFrameInterval;
		sl_uint32 m_bitrate;
		
	};
	
	class SLIB_EXPORT VideoDecoder : public Object
	{
		SLIB_DECLARE_OBJECT
		
	protected:
		VideoDecoder();
		
		~VideoDecoder();
		
	public:
		virtual sl_bool decode(const void* input, const sl_uint32& inputSize, VideoFrame& output) = 0;
		
	protected:
		sl_uint32 m_nWidth;
		sl_uint32 m_nHeight;
		
	};	
}

#endif
