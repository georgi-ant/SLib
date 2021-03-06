/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_MEDIA_CODEC_VPX
#define CHECKHEADER_SLIB_MEDIA_CODEC_VPX

#include "definition.h"

#include "video_codec.h"

namespace slib
{
	enum class VPXBitrateMode
	{
		Variable,
		Constant,
		ConstrainedQuality,
		ConstantQuality
	};
	
	class SLIB_EXPORT VP8EncoderParam
	{
	public:
		sl_uint32 width;
		sl_uint32 height;
		sl_uint32 framesPerSecond;
		sl_uint32 keyFrameInterval;
		sl_uint32 bitrate;
		sl_uint32 threadsCount;
		sl_uint32 cpuUsage;
		VPXBitrateMode bitrateMode;
		
	public:
		VP8EncoderParam();
		
		~VP8EncoderParam();
		
	};
	
	class SLIB_EXPORT VP8DecoderParam
	{
	public:
		sl_uint32 width;
		sl_uint32 height;
		
	public:
		VP8DecoderParam();
		
		~VP8DecoderParam();
		
	};
	
	class SLIB_EXPORT VP8Encoder : public VideoEncoder
	{
	public:
		VP8Encoder();
		
		~VP8Encoder();
		
	public:
		static Ref<VP8Encoder> create(const VP8EncoderParam& param);
		
	};
	
	class SLIB_EXPORT VP8Decoder : public VideoDecoder
	{
	public:
		VP8Decoder();
		
		~VP8Decoder();
		
	public:
		static Ref<VP8Decoder> create(const VP8DecoderParam& param);
		
	};	
}

#endif
