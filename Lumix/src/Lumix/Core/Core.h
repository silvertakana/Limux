#pragma once
#include <memory>

#ifdef LMX_PLATFORM_WINDOWS
#if LMX_DYNAMIC_LINK
	#ifdef  LMX_BUILD_DLL
		#define LMX_API __declspec(dllexport)
	#else
		#define LMX_API __declspec(dllimport)
	#endif //  LMX_BUILD_DLL 
#else
	#define LMX_API
#endif
#else
	#error Lumix only supports Windows!
#endif // _WIN32

#define BIT(x) (1<<x)
#define LMX_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace LMX
{

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}