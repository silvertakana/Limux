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
