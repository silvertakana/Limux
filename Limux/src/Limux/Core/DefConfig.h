#pragma once

#ifdef LMX_DIST
#else
	#define LMX_ENABLE_LOGGING
	#define LMX_ENABLE_ASSERTS
	#define LMX_PROFILE 1
#endif