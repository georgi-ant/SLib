
#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)

#elif defined(_WIN64)

#	include "platforms/x64_win/vp8_rtcd.h"

#elif defined(_WIN32)

#	include "platforms/x86_win/vp8_rtcd.h"

#elif defined(__APPLE__) && defined(__MACH__)
#		include <TargetConditionals.h>
#		if TARGET_OS_IOS
#			if TARGET_OS_SIMULATOR
#           	if defined(__x86_64__)
#					include "platforms/x64_ios_simulator/vp8_rtcd.h"
#				else
#					include "platforms/x86_ios_simulator/vp8_rtcd.h"
#				endif
#			else
#           	if defined(__arm64__)
#					include "platforms/arm64_ios/vp8_rtcd.h"
#				else
#					include "platforms/armv7_ios/vp8_rtcd.h"
#				endif
#			endif
#		elif TARGET_OS_MAC
#			include "platforms/x64_osx/vp8_rtcd.h"
#		endif

#elif defined(__ANDROID__)

#	if defined(__aarch64__) || defined(__arm64__)
#		include "platforms/arm64_android/vp8_rtcd.h"
#	elif defined(__arm__)
#		include "platforms/armv7_android/vp8_rtcd.h"
#	elif defined(__i386__)
#		include "platforms/x86_android/vp8_rtcd.h"
#	endif

#endif

