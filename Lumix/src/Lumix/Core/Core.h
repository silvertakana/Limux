#pragma once

#ifdef _WIN32
	#ifdef  LMX_BUILD_DLL
		#define LMX_API __declspec(dllexport)
	#else
		#define LMX_API __declspec(dllimport)
	#endif //  LMX_BUILD_DLL 
#else
	#error Lumix only supports Windows!
#endif // _WIN32

#define BIT(x) (1<<x)
#define LMX_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)